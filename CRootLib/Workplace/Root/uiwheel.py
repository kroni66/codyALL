if __USE_DYNAMIC_MODULE__:
	import pyapi

net = __import__(pyapi.GetModuleName("net"))

import ui, item, uitooltip, localeinfo

class WheelOfDestiny(ui.Window):
	def __init__(self):
		ui.Window.__init__(self)
		self.tooltipItem = uitooltip.ItemToolTip()
		self.tooltipItem.Hide()
		self.itemfortip = 0
		self.ItemIcon = None
		self.Turn = False
		self.Counter = 0
		self.Langsamer = 0
		self.Grad = 0
		self.Item = 0
		self.Random = 0
		self.GradZaehler = 0
		self.GUI = []
		self.BuildWindow()
		self.Hide()
		self.Board.Hide()

	def __del__(self):
		ui.Window.__del__(self)

	def BuildWindow(self):
		self.Board = ui.ExpandedImageBox()
		self.Board.AddFlag("movable")
		self.Board.AddFlag("float")
		self.Board.LoadImage("schicksal/schicksal_board.tga")
		self.Board.SetCenterPosition()
		self.Board.Show()
		
		self.Wheel = ui.ExpandedImageBox()
		self.Wheel.SetParent(self.Board)
		self.Wheel.LoadImage("schicksal/schicksal_rad.tga")
		self.Wheel.SetPosition(15, 45)
		self.Wheel.AddFlag("not_pick")
		self.Wheel.Show()
		
		self.CloseButton = ui.Button()
		self.CloseButton.SetParent(self.Board)
		self.CloseButton.SetEvent(ui.__mem_func__(self.ClosePacket))
		self.CloseButton.SetPosition(605, 45)
		self.CloseButton.SetUpVisual("d:/ymir work/ui/public/close_button_01.sub")
		self.CloseButton.SetOverVisual("d:/ymir work/ui/public/close_button_02.sub")
		self.CloseButton.SetDownVisual("d:/ymir work/ui/public/close_button_03.sub")
		self.CloseButton.Show()

		self.SlotBg = ui.ExpandedImageBox()
		self.SlotBg.SetParent(self.Board)
		self.SlotBg.SetPosition(553, 127)
		self.SlotBg.LoadImage("schicksal/slot.tga")
		self.SlotBg.AddFlag("not_pick")
		self.SlotBg.Show()

		self.Button = ui.Button()
		self.Button.SetParent(self.Wheel)
		self.Button.SetUpVisual("schicksal/schicksal_drehen_normal.tga")
		self.Button.SetOverVisual("schicksal/schicksal_drehen_over.tga")
		self.Button.SetDownVisual("schicksal/schicksal_drehen_down.tga")
		self.Button.SetPosition(177, 181)
		self.Button.SetEvent(lambda : net.WheelPacket(2))
		self.Button.Show()
		
		self.Yang = ui.TextLine()
		self.Yang.SetParent(self.Board)
		self.Yang.SetPosition(57, 576)
		self.Yang.SetFontColor(0.5, 1.0, 0.5)
		self.Yang.SetFontName("Arial:16")
		self.Yang.Show()
		
		self.FreeSpin = ui.TextLine()
		self.FreeSpin.SetParent(self.Board)
		self.FreeSpin.SetPosition(450, 574)
		self.FreeSpin.SetFontColor(0.5, 1.0, 0.5)
		self.FreeSpin.SetFontName("Arial:20")
		self.FreeSpin.Show()

	def TurnWheel(self, ItemId, Count, Spin, Random):
		self.Button.Disable()
		self.Langsamer = 10
		self.Item = int(ItemId)
		self.Counter = int(Spin)
		self.GradZaehler = 0
		self.Random = int(Random)
		pos = [225, 247, 269, 291, 315, 338, 1, 23, 45, 65, 88, 132, 109, 156, 178, 202]
		self.Grad = pos[self.Random]
		self.Turn = True

	def __BuildLastItem(self, path):
		self.ItemIcon = ui.ExpandedImageBox()
		self.ItemIcon.SetParent(self.SlotBg)
		self.ItemIcon.SetPosition(0, 0)
		self.ItemIcon.LoadImage(path)
		self.ItemIcon.Show()

	def SetIcons(self, vnum, count, number):
		number = int(number)
		item.SelectItem(int(vnum))
		itemIcon = item.GetIconImageFileName()
		ItemPosis = [
						[240, {"32":35, "64":20,"96":0}],
						[310, {"32":56, "64":36,"96":26}],
						[378, {"32":100, "64":80,"96":65}],
						[433, {"32":170, "64":143,"96":133}],
						[445, {"32":247, "64":227,"96":207}],
						[425, {"32":325, "64":305,"96":295}],
						[373, {"32":387, "64":367,"96":362}],
						[305, {"32":427, "64":408,"96":392}],
						[230, {"32":437, "64":420,"96":397}],
						[150, {"32":423, "64":400,"96":383}],
						[80, {"32":389, "64":355,"96":349}],
						[40, {"32":240, "64":218,"96":208}],
						[50, {"32":320, "64":300,"96":288}],
						[54, {"32":167, "64":140,"96":127}],
						[97, {"32":99, "64":79,"96":62}],
						[166, {"32":52, "64":32,"96":12}],
		]
		
		if number == 0:
			self.GUI = []
		
		IconImage = ui.ExpandedImageBox()
		IconImage.SetParent(self.Wheel)
		IconImage.LoadImage(itemIcon)
		IconImage.SetPosition(ItemPosis[number][0], ItemPosis[number][1][str(IconImage.GetHeight())])
		IconImage.AddFlag("not_pick")
		IconImage.Show()
		self.GUI.append(IconImage)

	def OnUpdate(self):
		if self.ItemIcon:
			if self.ItemIcon.IsIn():
				self.tooltipItem.SetItemToolTip(self.itemfortip)
			else:
				self.tooltipItem.HideToolTip()
		
		if self.Turn:
			if self.Counter > 0:
				self.Grad += self.Langsamer
				self.GradZaehler += self.Langsamer
				if self.GradZaehler >= 360:
					self.GradZaehler = 0
					self.Counter -= 1
			else:
				if self.Langsamer > 0:
					self.Langsamer -= 0.1
					self.Grad += self.Langsamer
				else:
					item.SelectItem(self.Item)
					self.__BuildLastItem(item.GetIconImageFileName())
					self.itemfortip = self.Item
					net.WheelPacket(3)
					self.Turn = False
					self.Button.Enable()
			
			self.Wheel.SetRotation(self.Grad)

	def ClosePacket(self):
		net.WheelPacket(1)

	def OnPressEscapeKey(self):
		self.ClosePacket()
		return True

	def Close(self):
		if self.IsShow():
			self.Board.Hide()
			self.Hide()	

	def Open(self, price, free):
		self.ItemIcon = None
		self.Wheel.SetRotation(0)
		self.FreeSpin.SetText(str(free))
		self.Yang.SetText(localeinfo.NumberToMoneyString(price))
		self.Board.Show()
		self.Show()
