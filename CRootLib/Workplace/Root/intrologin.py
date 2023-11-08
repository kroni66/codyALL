# -*- coding: latin-1 -*-
if __USE_DYNAMIC_MODULE__:
	import pyapi

app = __import__(pyapi.GetModuleName("app"))
net = __import__(pyapi.GetModuleName("net"))
import dbg
import ui
import ime
import snd
import wndMgr
import musicinfo
import ServerStateChecker
import serverinfo
import systemSetting
import constinfo
import uicommon
import time
import servercommandparser
import uiscriptlocale
import os
import uiweb
import localeinfo

IMG_PATH = "grafica/login/"

app.SetGuildMarkPath("test")

class ConnectingDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__LoadDialog()
		self.eventTimeOver = lambda *arg: None
		self.eventExit = lambda *arg: None

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadDialog(self):
		try:
			PythonScriptLoader = ui.PythonScriptLoader()
			PythonScriptLoader.LoadScriptFile(self, "uiscript/ConnectingDialog.py")
			self.board = self.GetChild("board")
			self.message = self.GetChild("message")
			self.countdownMessage = self.GetChild("countdown_message")

		except:
			import exception
			exception.Abort("ConnectingDialog.LoadDialog.BindObject")

	def Open(self, waitTime):
		curTime = time.clock()
		self.endTime = curTime + waitTime
		
		self.Lock()
		self.SetCenterPosition()
		self.SetTop()
		self.Show()

	def Close(self):
		self.Unlock()
		self.Hide()

	def Destroy(self):
		self.Hide()
		self.ClearDictionary()

	def SetText(self, text):
		self.message.SetText(text)

	def SetCountDownMessage(self, waitTime):
		self.countdownMessage.SetText("%.0f%s" % (waitTime, localeinfo.SECOND))

	def SAFE_SetTimeOverEvent(self, event):
		self.eventTimeOver = ui.__mem_func__(event)

	def SAFE_SetExitEvent(self, event):
		self.eventExit = ui.__mem_func__(event)

	def OnUpdate(self):
		lastTime = max(0, self.endTime - time.clock())
		if 0 == lastTime:
			self.Close()
			self.eventTimeOver()
		else:
			self.SetCountDownMessage(self.endTime - time.clock())

	def OnPressExitKey(self):
		#self.eventExit()
		return True

class LoginWindow(ui.ScriptWindow):
	def __init__(self, stream):
		ui.ScriptWindow.__init__(self)
		net.SetPhaseWindow(net.PHASE_WINDOW_LOGIN, self)
		net.SetAccountConnectorHandler(self)
		
		if app.ENABLE_MULTI_LANGUAGE:
			self.languageList = [ None, None, None, None, None, None, None, None, None, None ] #x10 languages
		
		self.connectingDialog = None
		self.stream=stream
		self.channelID = 1
		self.chBtn = {}

		self.saveTxts = {}
		self.saveAcceptBtns = {}
		self.saveDeleteBtns = {}
		self.popupX = 0
		self.popupY = 0
		self.questionDialog = None
		self.itemBuyQuestionDialog = None
		self.wndWeb = None

	def __del__(self):
		net.ClearPhaseWindow(net.PHASE_WINDOW_LOGIN, self)
		net.SetAccountConnectorHandler(0)
		ui.ScriptWindow.__del__(self)

	def Open(self):
		ServerStateChecker.Create(self)

		if not os.path.exists("UserData"):
			os.makedirs("UserData")

		if not os.path.exists(os.getcwd() + os.sep + "UserData\chatting"):
			os.mkdir(os.getcwd() + os.sep + "UserData\chatting")

		self.loginFailureMsgDict = {
			"ALREADY" : localeinfo.LOGIN_FAILURE_ALREAY,
			"NOID" : localeinfo.LOGIN_FAILURE_NOT_EXIST_ID,
			"WRONGPWD" : localeinfo.LOGIN_FAILURE_WRONG_PASSWORD,
			"FULL" : localeinfo.LOGIN_FAILURE_TOO_MANY_USER,
			"SHUTDOWN" : localeinfo.LOGIN_FAILURE_SHUTDOWN,
			"REPAIR" : localeinfo.LOGIN_FAILURE_REPAIR_ID,
			"BLOCK" : localeinfo.LOGIN_FAILURE_BLOCK_ID,
			"BESAMEKEY" : localeinfo.LOGIN_FAILURE_BE_SAME_KEY,
			"NOTAVAIL" : localeinfo.LOGIN_FAILURE_NOT_AVAIL,
			"NOBILL" : localeinfo.LOGIN_FAILURE_NOBILL,
			"BLKLOGIN" : localeinfo.LOGIN_FAILURE_BLOCK_LOGIN,
			"WEBBLK" : localeinfo.LOGIN_FAILURE_WEB_BLOCK,
			"BAN1" : localeinfo.LOGIN_FAILURE_BLOCK_ID,
			"BAN2" : localeinfo.LOGIN_FAILURE_BLOCK_ID,
			"UPDATE" : localeinfo.LOGIN_FAILURE_UPDATE,
		}

		self.loginFailureFuncDict = {
			"WRONGPWD"	: self.__DisconnectAndInputPassword,
			"QUIT"		: app.Exit,
		}
		
		self.SetSize(wndMgr.GetScreenWidth(), wndMgr.GetScreenHeight())
		self.SetWindowName("LoginWindow")
		if not self.__LoadScript("uiscript/loginwindow.py"):
			dbg.TraceError("LoginWindow.Open - __LoadScript Error")
			return
		
		self.wndWeb = uiweb.WebWindow(True)
		self.wndWeb.LoadWindow()
		self.wndWeb.Hide()
		
		if musicinfo.loginMusic != "":
			snd.SetMusicVolume(systemSetting.GetMusicVolume())
			snd.FadeInMusic("BGM/"+musicinfo.loginMusic)

		snd.SetSoundVolume(systemSetting.GetSoundVolume())

		# pevent key "[" "]"
		ime.AddExceptKey(91)
		ime.AddExceptKey(93)
		if app.ENABLE_MULTI_LANGUAGE:
			self.RefreshLanguagesBtn()
		
		self.Show()

		connectingIP = self.stream.GetConnectAddr()
		if connectingIP:
			self.__OpenLoginBoard()
		
		#self.setChannel(1)
		self.GetChannel()
		self.__RequestServerStateList()
		#self.__RefreshServerStateList()
		self.SetIDEditLineFocus()
		app.ShowCursor()

	def Close(self):
		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		ServerStateChecker.Initialize(self)

		print "---------------------------------------------------------------------------- CLOSE LOGIN WINDOW "

		if musicinfo.loginMusic != "" and musicinfo.selectMusic != "":
			snd.FadeOutMusic("BGM/"+musicinfo.loginMusic)
		
		if app.ENABLE_MULTI_LANGUAGE:
			self.languageList = [ None, None, None, None, None, None, None, None, None, None ] #x10 languages

		for i in xrange(6):
			self.chBtn[i] = None

		self.enterBtn = None
		self.saveAccountBtn = None
		self.exitBtn = None

		self.idEditLine.SetTabEvent(0)
		self.idEditLine.SetReturnEvent(0)
		self.idEditLine.SetEscapeEvent(0)
		self.pwdEditLine.SetReturnEvent(0)
		self.pwdEditLine.SetTabEvent(0)
		self.pwdEditLine.SetEscapeEvent(0)

		self.idEditLine.Hide()
		self.idEditLine = None
		self.pwdEditLine.Hide()
		self.pwdEditLine = None

		self.KillFocus()
		self.Hide()

		self.connectingDialog = None

		self.channelID = 1
		self.chBtn = {}
		
		for i in xrange(len(self.saveTxts)):
			self.saveTxts[i].Hide()
			self.saveTxts[i] = None
			self.saveAcceptBtns[i].Hide()
			self.saveAcceptBtns[i] = None
			self.saveDeleteBtns[i].Hide()
			self.saveDeleteBtns[i] = None
		self.saveTxts = {}
		self.saveAcceptBtns = {}
		self.saveDeleteBtns = {}

		self.stream.popupWindow.Close()
		self.loginFailureFuncDict=None
		if self.wndWeb:
			self.wndWeb.Destroy()
			self.wndWeb = None
		
		ime.ClearExceptKey()

		app.HideCursor()

	def __ExitGame(self):
		app.Exit()

	def SetIDEditLineFocus(self):
		if self.idEditLine != None:
			self.idEditLine.KillFocus()
			self.idEditLine.SetFocus()

	def SetPasswordEditLineFocus(self):
		if self.pwdEditLine != None:
			self.pwdEditLine.KillFocus()
			self.pwdEditLine.SetFocus()

	def OnEndCountDown(self):
		self.OnConnectFailure()

	def OnConnectFailure(self):
		snd.PlaySound("sound/ui/loginfail.wav")

		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		self.PopupNotifyMessage(localeinfo.LOGIN_CONNECT_FAILURE, self.SetPasswordEditLineFocus)

	def OnHandShake(self):
		snd.PlaySound("sound/ui/loginok.wav")
		self.PopupDisplayMessage(localeinfo.LOGIN_CONNECT_SUCCESS)

	def OnLoginStart(self):
		self.PopupDisplayMessage(localeinfo.LOGIN_PROCESSING)

	def OnLoginFailure(self, error):
		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		try:
			loginFailureMsg = self.loginFailureMsgDict[error]
		except KeyError:
			loginFailureMsg = localeinfo.LOGIN_FAILURE_UNKNOWN  + error

		if self.loginFailureFuncDict != None:
			loginFailureFunc=self.loginFailureFuncDict.get(error, self.SetPasswordEditLineFocus)
			self.PopupNotifyMessage(loginFailureMsg, loginFailureFunc)
			snd.PlaySound("sound/ui/loginfail.wav")

	def __DisconnectAndInputPassword(self):
		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		self.SetPasswordEditLineFocus()
		net.Disconnect()

	def NotifyChannelState(self, addrKey, state):
		try:
			stateName=serverinfo.STATE_DICT[state]
		except:
			stateName=serverinfo.STATE_NONE

		regionID=int(addrKey/1000)
		serverID=int(addrKey/10) % 100
		channelID=addrKey%10

		try:
			serverinfo.REGION_DICT[regionID][serverID]["channel"][channelID]["state"] = stateName
			self.__RefreshServerStateList()

		except:
			import exception
			exception.Abort(localeinfo.CHANNEL_NOT_FIND_INFO)

	def __RequestServerStateList(self):
		regionID = self.__GetRegionID()
		serverID = self.__GetServerID()

		try:
			channelDict = serverinfo.REGION_DICT[regionID][serverID]["channel"]
		except:
			print " __RequestServerStateList - serverinfo.REGION_DICT(%d, %d)" % (regionID, serverID)
			return

		ServerStateChecker.Initialize();
		for id, channelDataDict in channelDict.items():
			key=channelDataDict["key"]
			ip=channelDataDict["ip"]
			udp_port=channelDataDict["udp_port"]
			ServerStateChecker.AddChannel(key, ip, udp_port)

		ServerStateChecker.Request()
        
	def __RefreshServerStateList(self):

		regionID = self.__GetRegionID()
		serverID = self.__GetServerID()
		bakChannelID = self.__GetChannelID()

		try:
			channelDict = serverinfo.REGION_DICT[regionID][serverID]["channel"]
		except:
			print " __RequestServerStateList - serverinfo.REGION_DICT(%d, %d)" % (regionID, serverID)
			return

		for channelID, channelDataDict in channelDict.items():
			channelName = channelDataDict["name"]
			channelState = channelDataDict["state"]
			if channelID == self.__GetChannelID():
				self.channelStatus.SetText("CH %s: %s" % (str(self.__GetChannelID()), channelState))
                
	def __RefreshServerList(self):
		regionID = self.__GetRegionID()

		if not serverinfo.REGION_DICT.has_key(regionID):
			return

		self.serverList.ClearItem()

		regionDict = serverinfo.REGION_DICT[regionID]

		# SEVER_LIST_BUG_FIX
		visible_index = 1
		for id, regionDataDict in regionDict.items():
			name = regionDataDict.get("name", "noname")
			if localeinfo.IsBRAZIL() or localeinfo.IsCANADA():
				self.serverList.InsertItem(id, "%s" % (name))
			else:
				if localeinfo.IsCIBN10():
					if name[0] == "#":
						self.serverList.InsertItem(-1, "  %s" % (name[1:]))
					else:
						self.serverList.InsertItem(id, "  %s" % (name))
						visible_index += 1
				else:
					try:
						server_id = serverinfo.SERVER_ID_DICT[id]
					except:
						server_id = visible_index

					self.serverList.InsertItem(id, "  %02d. %s" % (int(server_id), name))

					visible_index += 1

		# END_OF_SEVER_LIST_BUG_FIX

	def GetChannel(self):
		try:
			file = open("channel.inf")
			lines = file.readlines()
			if len(lines) > 0:
				tokens = lines[0].split()
				ID = int(tokens[1])
			
			file.close()
			self.setChannel(ID)
		except:
			self.setChannel(1)

	def __SaveChannelInfo(self):
		try:
			file=open("channel.inf", "w")
			file.write("%d %d %d" % (self.__GetServerID(), self.__GetChannelID(), self.__GetRegionID()))
		except:
			print "LoginWindow.__SaveChannelInfo - SaveError"

	def __LoadScript(self, fileName):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, fileName)
		except:
			import exception
			exception.Abort("LoginWindow.__LoadScript.LoadObject")
		
		self.saveTxts = {}
		self.saveAcceptBtns = {}
		self.saveDeleteBtns = {}
		try:
			GetObject = self.GetChild
			self.idEditLine		= GetObject("ID_EditLine")
			self.pwdEditLine	= GetObject("Password_EditLine")
			self.btnExit		= GetObject("exit_button")
			self.loginButton	= GetObject("LoginButton")

			if app.ENABLE_MULTI_LANGUAGE:
				self.languageList[0] = GetObject("btn_lang_en")
				self.languageList[1] = GetObject("btn_lang_ro")
				self.languageList[2] = GetObject("btn_lang_it")
				self.languageList[3] = GetObject("btn_lang_tr")
				self.languageList[4] = GetObject("btn_lang_de")
				self.languageList[5] = GetObject("btn_lang_pl")
				self.languageList[6] = GetObject("btn_lang_pt")
				self.languageList[7] = GetObject("btn_lang_es")
				self.languageList[8] = GetObject("btn_lang_cz")
				self.languageList[9] = GetObject("btn_lang_hu")

			self.facebook = GetObject("facebook_btn")
			self.discord = GetObject("discord_btn")
			self.youtube = GetObject("youtube_btn")
			self.tiktok = GetObject("tiktok_btn")
			self.instagram = GetObject("instagram_btn")
			self.channelStatus = GetObject("chstatus")
			self.topPanel = GetObject("bg_top")
			for i in xrange(6):
				self.saveTxts[i] = GetObject("save_txt%d"%(i+1))
				self.saveAcceptBtns[i] = GetObject("loadacc_btn%d"%(i+1))
				self.saveDeleteBtns[i] = GetObject("deleteacc_btn%d"%(i+1))
				self.saveAcceptBtns[i].SetEvent(self.saveAccountData, i+1)
				self.saveDeleteBtns[i].SetEvent(self.delLoginButtonInfo, i+1)
				self.loadLoginInfoFromFile(i+1)
		except:
			import exception
			exception.Abort("LoginWindow.__LoadScript.BindObject")
		
		self.loginButton.SetEvent(ui.__mem_func__(self.__OnClickLoginButton))
		self.btnExit.SetEvent(ui.__mem_func__(self.__OnClickExitButton))
		self.facebook.SetEvent(ui.__mem_func__(self.__OpenWebSite), 0)
		self.discord.SetEvent(ui.__mem_func__(self.__OpenWebSite), 1)
		self.youtube.SetEvent(ui.__mem_func__(self.__OpenWebSite), 3)
		self.tiktok.SetEvent(ui.__mem_func__(self.__OpenWebSite), 4)
		self.instagram.SetEvent(ui.__mem_func__(self.__OpenWebSite), 5)
		
		if app.ENABLE_MULTI_LANGUAGE:
			self.languageList[0].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("en"))
			self.languageList[1].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("ro"))
			self.languageList[2].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("it"))
			self.languageList[3].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("tr"))
			self.languageList[4].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("de"))
			self.languageList[5].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("pl"))
			self.languageList[6].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("pt"))
			self.languageList[7].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("es"))
			self.languageList[8].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("cz"))
			self.languageList[9].SetEvent(lambda:ui.__mem_func__(self.__QuestionChangeLanguage)("hu"))
		
		self.idEditLine.SetReturnEvent(self.SetFocusPassEditLine)
		self.idEditLine.SetTabEvent(self.SetFocusPassEditLine)
		self.idEditLine.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))

		self.pwdEditLine.SetReturnEvent(ui.__mem_func__(self.__OnClickLoginButton))
		self.pwdEditLine.SetTabEvent(self.SetFocusIdEditLine)
		self.pwdEditLine.SetEscapeEvent(ui.__mem_func__(self.OnPressEscapeKey))

		self.chBtn = {}
		posesX = [51, 51, 51, 350, 350, 350]
		posesY = [1, 45, 89, 1, 45, 89]    
		text = ["CH1", "CH2", "CH3", "CH4", "CH5", "CH6"]

		for i in xrange(len(posesX) and len(posesY) and len(text)):
			self.chBtn[i] = ui.Button()
			self.chBtn[i].SetParent(self.topPanel)
			self.chBtn[i].SetPosition(posesX[i], posesY[i])
			self.chBtn[i].SetUpVisual(IMG_PATH + "ch_button0.tga")
			self.chBtn[i].SetOverVisual(IMG_PATH + "ch_button1.tga")
			self.chBtn[i].SetDownVisual(IMG_PATH + "ch_button2.tga")
			self.chBtn[i].SetText(text[i])   
			self.chBtn[i].SetEvent(self.setChannel, (i+1))
			self.chBtn[i].Show()
		
		(x, y) = self.chBtn[0].GetGlobalPosition()
		self.popupX = x + 40
		self.popupY = y + 8
		return 1

	if app.ENABLE_MULTI_LANGUAGE:
		def RefreshLanguagesBtn(self):
			langs = ["en", "ro", "it", "tr", "de", "pl", "pt", "es", "cz", "hu"]
			for i in xrange(10):
				if app.GetLocaleName() != langs[i]:
					self.languageList[i].SetUp()
				else:
					self.languageList[i].Down()

		def OnClickLanguageButton(self, lang):
			if app.GetLocaleName() != lang:
				with open("locale.cfg", "w+") as localeConfig:
					localeConfig.write("10022 %d %s" % (self.GetCodePage(lang), lang))
				
				app.SetDefaultCodePage(self.GetCodePage(lang))
				app.ForceSetLocale(lang, "locale/%s" % (lang))
				app.ShellExecute(".WoM2.exe")
				self.OnCloseQuestionDialog()
				app.Exit()

		def OnCloseQuestionDialog(self):
			if not self.questionDialog:
				return
			
			self.RefreshLanguagesBtn()
			self.questionDialog.Close()
			self.questionDialog = None
			constinfo.SET_ITEM_QUESTION_DIALOG_STATUS(0)

		def __QuestionChangeLanguage(self, lang):
			if app.GetLocaleName() == lang:
				return
			
			langs = ["en", "ro", "it", "tr", "de", "pl", "pt", "es", "cz", "hu"]
			for i in xrange(10):
				if lang != langs[i]:
					self.languageList[i].SetUp()
				else:
					self.languageList[i].Down()
			
			self.delLoginInfo(False)
			self.stream.popupWindow.Close()
			self.questionDialog = uicommon.QuestionDialog()
			self.questionDialog.SetText(localeinfo.QUESTION_DLG_CHANGELANGUAGE)
			self.questionDialog.SetAcceptEvent(lambda arg = lang: self.OnClickLanguageButton(arg))
			self.questionDialog.SetCancelEvent(self.OnCloseQuestionDialog)
			self.questionDialog.Open()
			self.questionDialog.SetPosition(self.popupX - 29, self.popupY)
			constinfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)

	def GetCodePage(self, lang):
		codePageDict = {
			"en" : 1252,
			"ro" : 1250,
			"it" : 1252,
			"tr" : 1254,
			"de" : 1252,
			"pl" : 1250,
			"pt" : 1252,
			"es" : 1252,
			"cz" : 1250,
			"hu" : 1250,
		}
		try:
			return codePageDict[lang]
		except:
			return 1252

	def GetIndexByName(self, lang):
		langCode = {
			"en" : 0, # 0
			"ro" : 1, # 1
			"it" : 2, # 2
			"tr" : 3, # 3
			"de" : 4, # 4
			"pl" : 5, # 5
			"pt" : 6, # 6
			"es" : 7, # 7
			"cz" : 8, # 8
			"hu" : 9, # 9
		}
		try:
			return langCode[lang]
		except:
			return 2

	def SetFocusIdEditLine(self):
		self.idEditLine.KillFocus()
		self.idEditLine.SetFocus()

	def SetFocusPassEditLine(self):
		self.pwdEditLine.SetFocus()

	def saveAccountData(self, accID):
		if self.saveTxts[accID-1].GetText() == str(localeinfo.EMPTY_SLOT % (accID)):
			id = self.idEditLine.GetText()
			pwd = self.pwdEditLine.GetText()

			if len(id) == 0:
				self.PopupNotifyMessage(localeinfo.LOGIN_INPUT_ID, self.SetIDEditLineFocus)
				return

			if len(pwd) == 0:
				self.PopupNotifyMessage(localeinfo.LOGIN_INPUT_PASSWORD, self.SetPasswordEditLineFocus)
				return
			f = old_open("UserData/acc%d"%accID, 'w')
			try:
				f.write("%s\t%s"%(id, pwd))
			finally:
				f.close()
			self.saveTxts[accID-1].SetText("%d. %s"%(accID, id))
			self.saveTxts[accID-1].SetPackedFontColor(0xFFDBB06E)
		else:
			self.loadLoginInfo(accID)

	def loadLoginInfo(self, accID):
		if os.path.isfile("UserData/acc%d"%accID):
			f = old_open("UserData/acc%d"%accID, 'r')
			try:
				for line in f:
					if line == "":
						break
					data = line.split('\t')
					self.idEditLine.SetText(data[0])
					self.pwdEditLine.SetText(data[1])

					if len(self.idEditLine.GetText()) > 0 and len(self.pwdEditLine.GetText()) > 0:
						self.__OnClickLoginButton()
			finally:
				f.close()

	def loadLoginInfoFromFile(self, accID):
		if os.path.isfile("UserData/acc%d"%accID):
			f = old_open("UserData/acc%d"%accID, 'r')
			try:
				for line in f:
					if line == "":
						break
					data = line.split('\t')
					self.saveTxts[accID-1].SetText("%d. %s"%(accID, data[0]))
					self.saveTxts[accID-1].SetPackedFontColor(0xFFDBB06E)
			finally:
				f.close()
		else:
			self.saveTxts[accID-1].SetText(localeinfo.EMPTY_SLOT % (accID))
			self.saveTxts[accID-1].SetPackedFontColor(0xFF544D43)

	def delLoginButtonInfo(self, accID):
		if os.path.isfile("UserData/acc%d" % accID):
			accountName = ""
			f = old_open("UserData/acc%d"%accID, 'r')
			try:
				for line in f:
					if line == "":
						break
					
					data = line.split('\t')
					accountName = data[0]
			finally:
				f.close()
			
			self.stream.popupWindow.Close()
			self.OnCloseQuestionDialog()
			itemBuyQuestionDialog = uicommon.QuestionDialog()
			itemBuyQuestionDialog.SetText(localeinfo.QUESTION_DLG_REMOVEACC % accountName)
			itemBuyQuestionDialog.SetAcceptEvent(lambda arg=True: self.delLoginInfo(arg))
			itemBuyQuestionDialog.SetCancelEvent(lambda arg=False: self.delLoginInfo(arg))
			itemBuyQuestionDialog.Open()
			itemBuyQuestionDialog.accID = accID
			itemBuyQuestionDialog.SetPosition(self.popupX - 29, self.popupY)
			self.itemBuyQuestionDialog = itemBuyQuestionDialog

	def delLoginInfo(self, arg):
		if not self.itemBuyQuestionDialog:
			return

		accID = self.itemBuyQuestionDialog.accID

		if arg:
			if os.path.isfile("UserData/acc%d"%accID):
				os.remove("UserData/acc%d"%accID)
				self.saveTxts[accID-1].SetText("%d. Spazio libero"%accID)
				self.saveTxts[accID-1].SetPackedFontColor(0xFF544D43)

		self.itemBuyQuestionDialog.Close()
		self.itemBuyQuestionDialog = None

	def setChannel(self, channel):
		self.channelID = channel
		for i in xrange(len(self.chBtn)):
			if channel-1 == i:
				self.chBtn[i].Down()
				self.chBtn[i].Disable()
			else:
				self.chBtn[i].SetUp()
				self.chBtn[i].Enable()
		self.__OnClickSelectServerButton()
		#self.NotifyChannelState()
		self.__RefreshServerStateList()

	def DoNothing(self):
		pass

	def Connect(self, id, pwd):
		#if not app.W2Loaded():
		#	self.OnCloseQuestionDialog()
		#	self.stream.popupWindow.Close()
		#	self.stream.popupWindow.Open(localeinfo.GAME_NOT_LOADED, self.DoNothing, localeinfo.UI_OK, self.popupX, self.popupY)
		#	return
		
		if constinfo.SEQUENCE_PACKET_ENABLE:
			net.SetPacketSequenceMode()
		
		self.OnCloseQuestionDialog()
		self.delLoginInfo(False)
		self.stream.popupWindow.Close()
		self.stream.popupWindow.Open(localeinfo.LOGIN_CONNETING, self.SetPasswordEditLineFocus, localeinfo.UI_CANCEL, self.popupX, self.popupY)

		constinfo.ACCOUNT_NAME = str(id)
		try:
			self.stream.SetLoginInfo(id, pwd)
		except:
			self.stream.SetLoginInfo(id, pwd, 1234)
		self.stream.Connect()

	def __OnClickExitButton(self):
		self.stream.SetPhaseWindow(0)

	def __SetServerInfo(self, name):
		net.SetServerInfo(name.strip())

	def PopupDisplayMessage(self, msg):
		self.OnCloseQuestionDialog()
		self.delLoginInfo(False)
		self.stream.popupWindow.Close()
		self.stream.popupWindow.Open(msg, 0, localeinfo.UI_CANCEL, self.popupX, self.popupY)

	def PopupNotifyMessage(self, msg, func=0):
		if not func:
			func=self.EmptyFunc
		
		self.OnCloseQuestionDialog()
		self.delLoginInfo(False)
		self.stream.popupWindow.Close()
		self.stream.popupWindow.Open(msg, func, localeinfo.UI_OK, self.popupX, self.popupY)

	def OnPressExitKey(self):
		self.stream.popupWindow.Close()
		self.stream.SetPhaseWindow(0)
		return True

	def EmptyFunc(self):
		pass

	#####################################################################################
	def __GetRegionID(self):
		return 0

	def __GetServerID(self):
		#return self.serverList.GetSelectedItem()
		return 1
        
	def __GetChannelID(self):
		return self.channelID

	def __OpenLoginBoard(self):
		if self.idEditLine == None:
			self.idEditLine.SetText("")
		if self.pwdEditLine == None:
			self.pwdEditLine.SetText("")

		self.idEditLine.KillFocus()
		self.idEditLine.SetFocus()

	def __OnClickSelectServerButton(self):
		regionID = 0
		serverID = 1
		channelID = self.__GetChannelID()

		if (not serverinfo.REGION_DICT.has_key(regionID)):
			self.PopupNotifyMessage(localeinfo.CHANNEL_SELECT_REGION)
			return

		if (not serverinfo.REGION_DICT[regionID].has_key(serverID)):
			self.PopupNotifyMessage(localeinfo.CHANNEL_SELECT_SERVER)
			return

		try:
			channelDict = serverinfo.REGION_DICT[regionID][serverID]["channel"]
		except KeyError:
			return

		try:
			state = channelDict[channelID]["state"]
		except KeyError:
			self.PopupNotifyMessage(localeinfo.CHANNEL_SELECT_CHANNEL)
			return

		if state == serverinfo.STATE_DICT[3]: 
			self.PopupNotifyMessage(localeinfo.CHANNEL_NOTIFY_FULL)
			return

		self.__SaveChannelInfo()
        
		try:
			serverName = serverinfo.REGION_DICT[regionID][serverID]["name"]
			channelName = serverinfo.REGION_DICT[regionID][serverID]["channel"][channelID]["name"]
			addrKey = serverinfo.REGION_DICT[regionID][serverID]["channel"][channelID]["key"]
		except:
			serverName = localeinfo.CHANNEL_EMPTY_SERVER
			channelName = localeinfo.CHANNEL_NORMAL % channelID

		self.__SetServerInfo("%s, %s " % (serverName, channelName))

		try:
			ip = serverinfo.REGION_DICT[regionID][serverID]["channel"][channelID]["ip"]
			tcp_port = serverinfo.REGION_DICT[regionID][serverID]["channel"][channelID]["tcp_port"]
		except:
			import exception
			exception.Abort("LoginWindow.__OnClickSelectServerButton")

		try:
			account_ip = serverinfo.REGION_AUTH_SERVER_DICT[regionID][serverID]["ip"]
			account_port = serverinfo.REGION_AUTH_SERVER_DICT[regionID][serverID]["port"]
		except:
			account_ip = 0
			account_port = 0

		try:
			markKey = regionID*1000 + serverID*10
			markAddrValue=serverinfo.MARKADDR_DICT[markKey]
			net.SetMarkServer(markAddrValue["ip"], markAddrValue["tcp_port"])
			app.SetGuildMarkPath(markAddrValue["mark"])
			# GUILD_SYMBOL
			app.SetGuildSymbolPath(markAddrValue["symbol_path"])
			# END_OF_GUILD_SYMBOL

		except:
			import exception
			exception.Abort("LoginWindow.__OnClickSelectServerButton")

		self.stream.SetConnectInfo(ip, tcp_port, account_ip, account_port)

	def __OnClickLoginButton(self):
		id = self.idEditLine.GetText()
		pwd = self.pwdEditLine.GetText()		

		if len(self.idEditLine.GetText()) == 0:
			self.PopupNotifyMessage(localeinfo.LOGIN_INPUT_ID, self.SetIDEditLineFocus)
			return

		if len(self.pwdEditLine.GetText()) == 0:
			self.PopupNotifyMessage(localeinfo.LOGIN_INPUT_PASSWORD, self.SetPasswordEditLineFocus)
			return

		self.Connect(id, pwd)

	def OnUpdate(self):
		if constinfo.restart == 1:
			app.ShellExecute(".WoM2.exe")
			app.Exit()
		
		ServerStateChecker.Update()

	def OnPressEscapeKey(self):
		self.stream.popupWindow.Close()
		self.stream.SetPhaseWindow(0)
		return True

	def __OpenWebSite(self, idToOpen):
		if not self.wndWeb:
			return
		
		if self.wndWeb.IsShow():
			return
		
		if idToOpen == 0:
			self.wndWeb.Open("https://wom2.global/")
		elif idToOpen == 1:
			self.wndWeb.Open("https://wom2.global/")
		elif idToOpen == 3:
			self.wndWeb.Open("https://wom2.global/")
		elif idToOpen == 4:
			self.wndWeb.Open("https://wom2.global/")
		elif idToOpen == 5:
			self.wndWeb.Open("https://wom2.global/")
