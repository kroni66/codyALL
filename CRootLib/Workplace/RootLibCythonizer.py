from sys import path as sys_path
from os.path import splitext as op_splitext

libpath = r'..\Py2Lib\lib'
sys_path.append(libpath)
rootpath = r'.'

capNameList = {
	"colorinfo":"colorinfo",
	"consolemodule":"consolemodule",
	"constinfo":"constinfo",
	"dailygift":"dailygift",
	"debuginfo":"debuginfo",
	"dragon_soul_refine_settings":"dragon_soul_refine_settings",
	"emotion":"emotion",
	"exception":"exception",
	"game":"game",
	"ingamewiki":"ingamewiki",
	"ingamewikiconfig":"ingamewikiconfig",
	"ingamewikiui":"ingamewikiui",
	"interfacemodule":"interfacemodule",
	"introcreate":"introcreate",
	"introempire":"introempire",
	"introloading":"introloading",
	"intrologin":"intrologin",
	"introselect":"introselect",
	"localeinfo":"localeinfo",
	"marek38":"marek38",
	"mousemodule":"mousemodule",
	"musicinfo":"musicinfo",
	"networkmodule":"networkmodule",
	"playersettingmodule":"playersettingmodule",
	"prototype":"prototype",
	"servercommandparser":"servercommandparser",
	"serverinfo":"serverinfo",
	"stringcommander":"stringcommander",
	"system":"system",
	"test_affect":"test_affect",
	"ui":"ui",
	"uiacce":"uiacce",
	"uiaffectshower":"uiaffectshower",
	"uiattachmetin":"uiattachmetin",
	"uiattrdialog":"uiattrdialog",
	"uiattrtransfer":"uiattrtransfer",
	"uiauction":"uiauction",
	"uiautoban":"uiautoban",
	"uibattlepass":"uibattlepass",
	"uibattleroyale":"uibattleroyale",
	"uibiolog":"uibiolog",
	"uicandidate":"uicandidate",
	"uichannel":"uichannel",
	"uicharacter":"uicharacter",
	"uicharacterdetails":"uicharacterdetails",
	"uichat":"uichat",
	"uicommon":"uicommon",
	"uicube":"uicube",
	"uicuberenewal":"uicuberenewal",
	"uidoctrinechoose":"uidoctrinechoose",
	"uidragonlairranking":"uidragonlairranking",
	"uidragonsoul":"uidragonsoul",
	"uiduel":"uiduel",
	"uidungeoninfo":"uidungeoninfo",
	"uiequipmentdialog":"uiequipmentdialog",
	"uiex":"uiex",
	"uiexchange":"uiexchange",
	"uiextrainventory":"uiextrainventory",
	"uifishing":"uifishing",
	"uigamebutton":"uigamebutton",
	"uigameoption":"uigameoption",
	"uiguild":"uiguild",
	"uiguildrank":"uiguildrank",
	"uiinventory":"uiinventory",
	"uimapnameshower":"uimapnameshower",
	"uimarketsystem":"uimarketsystem",
	"uimessenger":"uimessenger",
	"uiminimap":"uiminimap",
	"uiofflineshop":"uiofflineshop",
	"uioption":"uioption",
	"uiparty":"uiparty",
	"uipetenchant":"uipetenchant",
	"uipetevownd":"uipetevownd",
	"uipetfeed":"uipetfeed",
	"uipetincubatrice":"uipetincubatrice",
	"uipetsystem":"uipetsystem",
	"uiphasecurtain":"uiphasecurtain",
	"uipickmoney":"uipickmoney",
	"uiplayergauge":"uiplayergauge",
	"uipointreset":"uipointreset",
	"uiprivateshopbuilder":"uiprivateshopbuilder",
	"uiquest":"uiquest",
	"uiranking":"uiranking",
	"uirefine":"uirefine",
	"uirestart":"uirestart",
	"uirune":"uirune",
	"uisafebox":"uisafebox",
	"uisavepoint":"uisavepoint",
	"uiscriptlocale":"uiscriptlocale",
	"uiselectitem":"uiselectitem",
	"uiselectmusic":"uiselectmusic",
	"uishop":"uishop",
	"uiskillcolor":"uiskillcolor",
	"uiswitchbot":"uiswitchbot",
	"uisystem":"uisystem",
	"uisystemgems":"uisystemgems",
	"uisystemoption":"uisystemoption",
	"uitarget":"uitarget",
	"uitaskbar":"uitaskbar",
	"uiteleporter":"uiteleporter",
	"uitip":"uitip",
	"uitooltip":"uitooltip",
	"uiuploadmark":"uiuploadmark",
	"uiweb":"uiweb",
	"uiwheel":"uiwheel",
	"uiwhisper":"uiwhisper",
	"utils":"utils",
	"whispermanager":"whispermanager",
}

def checkCapName(x):
	base, ext = op_splitext(x)
	try:
		return capNameList[base.lower()] + ext
	except KeyError:
		return x

import imp
fp, pathname, description = imp.find_module('utils', [libpath])
utils = imp.load_module('utils', fp, pathname, description)

pys = utils.findMatchedFiles(rootpath, "*.py")
if __file__ in pys:
	pys.remove(__file__)
pys = [checkCapName(x) for x in pys]

import cythonizer
moduleLst = cythonizer.run(pys, forceRecompile=True)
moduleNameLst = []
sourceFileLst = []

for m in moduleLst:
	for source in m.sources:
		base, ext = op_splitext(source)
		moduleName = base.split('/')[-1]
		moduleNameLst.append(moduleName)
		sourceFileLst.append(base + (".cpp" if "c++" == m.language else ".c"))

import sourceWriter
sourceFileName = sourceWriter.run(moduleNameLst, 'rootlib')
print "%s successfully created." % sourceFileName

