if __USE_DYNAMIC_MODULE__:
	import pyapi

app = __import__(pyapi.GetModuleName("app"))
import localeinfo

app.ServerName = None

SRV1 = {
	"name":"WoM2",
	#test
	#"host":"193.84.64.175",
	#live
	"host" : "146.59.82.108",
	"auth1":30052,
	"ch1":30054,
	"ch2":30058,
	"ch3":30062,
	"ch4":30066,
	"ch5":30070,
	"ch6":30074,
}

STATE_NONE = "|cFFFF0000Offline"

STATE_DICT = {
	0 : "|cFFFF0000Non Disponibile",
	1 : "|cFF17EA17Online",
	2 : "|cFFFF4500Occupato",
	3 : "|cFFFF0000Pieno"
}

SERVER1_CHANNEL_DICT = {
	1:{"key":11,"name":"Channel 1","ip":SRV1["host"],"tcp_port":SRV1["ch1"],"udp_port":SRV1["ch1"],"state":STATE_NONE,},
	2:{"key":12,"name":"Channel 2","ip":SRV1["host"],"tcp_port":SRV1["ch2"],"udp_port":SRV1["ch2"],"state":STATE_NONE,},
	3:{"key":13,"name":"Channel 3","ip":SRV1["host"],"tcp_port":SRV1["ch3"],"udp_port":SRV1["ch3"],"state":STATE_NONE,},
	4:{"key":14,"name":"Channel 4","ip":SRV1["host"],"tcp_port":SRV1["ch4"],"udp_port":SRV1["ch4"],"state":STATE_NONE,},
	5:{"key":15,"name":"Channel 5","ip":SRV1["host"],"tcp_port":SRV1["ch5"],"udp_port":SRV1["ch5"],"state":STATE_NONE,},
	6:{"key":16,"name":"Channel 6","ip":SRV1["host"],"tcp_port":SRV1["ch6"],"udp_port":SRV1["ch6"],"state":STATE_NONE,},
}

REGION_NAME_DICT = {
	0 : SRV1["name"],
}

REGION_AUTH_SERVER_DICT = {
	0 : {
		1 : { "ip":SRV1["host"], "port":SRV1["auth1"], },
		2 : { "ip":SRV1["host"], "port":SRV1["auth1"], },
		3 : { "ip":SRV1["host"], "port":SRV1["auth1"], },
		4 : { "ip":SRV1["host"], "port":SRV1["auth1"], },
		5 : { "ip":SRV1["host"], "port":SRV1["auth1"], },
		6 : { "ip":SRV1["host"], "port":SRV1["auth1"], },
	}
}

REGION_DICT = {
	0 : {
		1 : { "name" :SRV1["name"], "channel" : SERVER1_CHANNEL_DICT, },
	},
}

MARKADDR_DICT = {
	10 : { "ip" : SRV1["host"], "tcp_port" : SRV1["ch1"], "mark" : "10.tga", "symbol_path" : "10", },
}

TESTADDR = { "ip" : SRV1["host"], "tcp_port" : SRV1["ch1"], "udp_port" : SRV1["ch1"], }