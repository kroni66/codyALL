#include "PythonrootlibManager.h"
#include "Python.h"
#ifdef _DEBUG
	#pragma comment (lib, "rootlib_d.lib")
#else
	#pragma comment (lib, "rootlib.lib")
#endif

struct rootlib_SMethodDef
{
	char* func_name;
	void (*func)();
};

PyMODINIT_FUNC initcolorinfo();
PyMODINIT_FUNC initconsolemodule();
PyMODINIT_FUNC initconstinfo();
PyMODINIT_FUNC initdailygift();
PyMODINIT_FUNC initdebuginfo();
PyMODINIT_FUNC initdragon_soul_refine_settings();
PyMODINIT_FUNC initemotion();
PyMODINIT_FUNC initexception();
PyMODINIT_FUNC initgame();
PyMODINIT_FUNC initingamewiki();
PyMODINIT_FUNC initingamewikiconfig();
PyMODINIT_FUNC initingamewikiui();
PyMODINIT_FUNC initinterfacemodule();
PyMODINIT_FUNC initintrocreate();
PyMODINIT_FUNC initintroempire();
PyMODINIT_FUNC initintroloading();
PyMODINIT_FUNC initintrologin();
PyMODINIT_FUNC initintroselect();
PyMODINIT_FUNC initlocaleinfo();
PyMODINIT_FUNC initmarek38();
PyMODINIT_FUNC initmousemodule();
PyMODINIT_FUNC initmusicinfo();
PyMODINIT_FUNC initnetworkmodule();
PyMODINIT_FUNC initplayersettingmodule();
PyMODINIT_FUNC initprototype();
PyMODINIT_FUNC initservercommandparser();
PyMODINIT_FUNC initserverinfo();
PyMODINIT_FUNC initstringcommander();
PyMODINIT_FUNC initsystem();
PyMODINIT_FUNC inittest_affect();
PyMODINIT_FUNC initui();
PyMODINIT_FUNC inituiacce();
PyMODINIT_FUNC inituiaffectshower();
PyMODINIT_FUNC inituiattachmetin();
PyMODINIT_FUNC inituiattrdialog();
PyMODINIT_FUNC inituiattrtransfer();
PyMODINIT_FUNC inituiauction();
PyMODINIT_FUNC inituiautoban();
PyMODINIT_FUNC inituibattlepass();
PyMODINIT_FUNC inituibattleroyale();
PyMODINIT_FUNC inituibiolog();
PyMODINIT_FUNC inituicandidate();
PyMODINIT_FUNC inituichannel();
PyMODINIT_FUNC inituicharacter();
PyMODINIT_FUNC inituicharacterdetails();
PyMODINIT_FUNC inituichat();
PyMODINIT_FUNC inituicommon();
PyMODINIT_FUNC inituicube();
PyMODINIT_FUNC inituicuberenewal();
PyMODINIT_FUNC inituidoctrinechoose();
PyMODINIT_FUNC inituidragonlairranking();
PyMODINIT_FUNC inituidragonsoul();
PyMODINIT_FUNC inituiduel();
PyMODINIT_FUNC inituidungeoninfo();
PyMODINIT_FUNC inituiequipmentdialog();
PyMODINIT_FUNC inituiex();
PyMODINIT_FUNC inituiexchange();
PyMODINIT_FUNC inituiextrainventory();
PyMODINIT_FUNC inituifishing();
PyMODINIT_FUNC inituigamebutton();
PyMODINIT_FUNC inituigameoption();
PyMODINIT_FUNC inituiguild();
PyMODINIT_FUNC inituiguildrank();
PyMODINIT_FUNC inituiinventory();
PyMODINIT_FUNC inituimapnameshower();
PyMODINIT_FUNC inituimarketsystem();
PyMODINIT_FUNC inituimessenger();
PyMODINIT_FUNC inituiminimap();
PyMODINIT_FUNC inituiofflineshop();
PyMODINIT_FUNC inituioption();
PyMODINIT_FUNC inituiparty();
PyMODINIT_FUNC inituipetenchant();
PyMODINIT_FUNC inituipetevownd();
PyMODINIT_FUNC inituipetfeed();
PyMODINIT_FUNC inituipetincubatrice();
PyMODINIT_FUNC inituipetsystem();
PyMODINIT_FUNC inituiphasecurtain();
PyMODINIT_FUNC inituipickmoney();
PyMODINIT_FUNC inituiplayergauge();
PyMODINIT_FUNC inituipointreset();
PyMODINIT_FUNC inituiprivateshopbuilder();
PyMODINIT_FUNC inituiquest();
PyMODINIT_FUNC inituiranking();
PyMODINIT_FUNC inituirefine();
PyMODINIT_FUNC inituirestart();
PyMODINIT_FUNC inituirune();
PyMODINIT_FUNC inituisafebox();
PyMODINIT_FUNC inituisavepoint();
PyMODINIT_FUNC inituiscriptlocale();
PyMODINIT_FUNC inituiselectitem();
PyMODINIT_FUNC inituiselectmusic();
PyMODINIT_FUNC inituishop();
PyMODINIT_FUNC inituiskillcolor();
PyMODINIT_FUNC inituiswitchbot();
PyMODINIT_FUNC inituisystem();
PyMODINIT_FUNC inituisystemgems();
PyMODINIT_FUNC inituisystemoption();
PyMODINIT_FUNC inituitarget();
PyMODINIT_FUNC inituitaskbar();
PyMODINIT_FUNC inituiteleporter();
PyMODINIT_FUNC inituitip();
PyMODINIT_FUNC inituitooltip();
PyMODINIT_FUNC inituiuploadmark();
PyMODINIT_FUNC inituiweb();
PyMODINIT_FUNC inituiwheel();
PyMODINIT_FUNC inituiwhisper();
PyMODINIT_FUNC initutils();
PyMODINIT_FUNC initwhispermanager();

rootlib_SMethodDef rootlib_init_methods[] =
{
	{ "colorinfo", initcolorinfo },
	{ "consolemodule", initconsolemodule },
	{ "constinfo", initconstinfo },
	{ "dailygift", initdailygift },
	{ "debuginfo", initdebuginfo },
	{ "dragon_soul_refine_settings", initdragon_soul_refine_settings },
	{ "emotion", initemotion },
	{ "exception", initexception },
	{ "game", initgame },
	{ "ingamewiki", initingamewiki },
	{ "ingamewikiconfig", initingamewikiconfig },
	{ "ingamewikiui", initingamewikiui },
	{ "interfacemodule", initinterfacemodule },
	{ "introcreate", initintrocreate },
	{ "introempire", initintroempire },
	{ "introloading", initintroloading },
	{ "intrologin", initintrologin },
	{ "introselect", initintroselect },
	{ "localeinfo", initlocaleinfo },
	{ "marek38", initmarek38 },
	{ "mousemodule", initmousemodule },
	{ "musicinfo", initmusicinfo },
	{ "networkmodule", initnetworkmodule },
	{ "playersettingmodule", initplayersettingmodule },
	{ "prototype", initprototype },
	{ "servercommandparser", initservercommandparser },
	{ "serverinfo", initserverinfo },
	{ "stringcommander", initstringcommander },
	{ "system", initsystem },
	{ "test_affect", inittest_affect },
	{ "ui", initui },
	{ "uiacce", inituiacce },
	{ "uiaffectshower", inituiaffectshower },
	{ "uiattachmetin", inituiattachmetin },
	{ "uiattrdialog", inituiattrdialog },
	{ "uiattrtransfer", inituiattrtransfer },
	{ "uiauction", inituiauction },
	{ "uiautoban", inituiautoban },
	{ "uibattlepass", inituibattlepass },
	{ "uibattleroyale", inituibattleroyale },
	{ "uibiolog", inituibiolog },
	{ "uicandidate", inituicandidate },
	{ "uichannel", inituichannel },
	{ "uicharacter", inituicharacter },
	{ "uicharacterdetails", inituicharacterdetails },
	{ "uichat", inituichat },
	{ "uicommon", inituicommon },
	{ "uicube", inituicube },
	{ "uicuberenewal", inituicuberenewal },
	{ "uidoctrinechoose", inituidoctrinechoose },
	{ "uidragonlairranking", inituidragonlairranking },
	{ "uidragonsoul", inituidragonsoul },
	{ "uiduel", inituiduel },
	{ "uidungeoninfo", inituidungeoninfo },
	{ "uiequipmentdialog", inituiequipmentdialog },
	{ "uiex", inituiex },
	{ "uiexchange", inituiexchange },
	{ "uiextrainventory", inituiextrainventory },
	{ "uifishing", inituifishing },
	{ "uigamebutton", inituigamebutton },
	{ "uigameoption", inituigameoption },
	{ "uiguild", inituiguild },
	{ "uiguildrank", inituiguildrank },
	{ "uiinventory", inituiinventory },
	{ "uimapnameshower", inituimapnameshower },
	{ "uimarketsystem", inituimarketsystem },
	{ "uimessenger", inituimessenger },
	{ "uiminimap", inituiminimap },
	{ "uiofflineshop", inituiofflineshop },
	{ "uioption", inituioption },
	{ "uiparty", inituiparty },
	{ "uipetenchant", inituipetenchant },
	{ "uipetevownd", inituipetevownd },
	{ "uipetfeed", inituipetfeed },
	{ "uipetincubatrice", inituipetincubatrice },
	{ "uipetsystem", inituipetsystem },
	{ "uiphasecurtain", inituiphasecurtain },
	{ "uipickmoney", inituipickmoney },
	{ "uiplayergauge", inituiplayergauge },
	{ "uipointreset", inituipointreset },
	{ "uiprivateshopbuilder", inituiprivateshopbuilder },
	{ "uiquest", inituiquest },
	{ "uiranking", inituiranking },
	{ "uirefine", inituirefine },
	{ "uirestart", inituirestart },
	{ "uirune", inituirune },
	{ "uisafebox", inituisafebox },
	{ "uisavepoint", inituisavepoint },
	{ "uiscriptlocale", inituiscriptlocale },
	{ "uiselectitem", inituiselectitem },
	{ "uiselectmusic", inituiselectmusic },
	{ "uishop", inituishop },
	{ "uiskillcolor", inituiskillcolor },
	{ "uiswitchbot", inituiswitchbot },
	{ "uisystem", inituisystem },
	{ "uisystemgems", inituisystemgems },
	{ "uisystemoption", inituisystemoption },
	{ "uitarget", inituitarget },
	{ "uitaskbar", inituitaskbar },
	{ "uiteleporter", inituiteleporter },
	{ "uitip", inituitip },
	{ "uitooltip", inituitooltip },
	{ "uiuploadmark", inituiuploadmark },
	{ "uiweb", inituiweb },
	{ "uiwheel", inituiwheel },
	{ "uiwhisper", inituiwhisper },
	{ "utils", initutils },
	{ "whispermanager", initwhispermanager },
	{ NULL, NULL },
};

static PyObject* rootlib_isExist(PyObject *self, PyObject *args)
{
	char* func_name;

	if(!PyArg_ParseTuple(args, "s", &func_name))
		return NULL;

	for (int i = 0; NULL != rootlib_init_methods[i].func_name;i++)
	{
		if (0 == _stricmp(rootlib_init_methods[i].func_name, func_name))
		{
			return Py_BuildValue("i", 1);
		}
	}
	return Py_BuildValue("i", 0);
}

static PyObject* rootlib_moduleImport(PyObject *self, PyObject *args)
{
	char* func_name;

	if(!PyArg_ParseTuple(args, "s", &func_name))
		return NULL;

	for (int i = 0; NULL != rootlib_init_methods[i].func_name;i++)
	{
		if (0 == _stricmp(rootlib_init_methods[i].func_name, func_name))
		{
			rootlib_init_methods[i].func();
			if (PyErr_Occurred())
				return NULL;
			PyObject* m = PyDict_GetItemString(PyImport_GetModuleDict(), rootlib_init_methods[i].func_name);
			if (m == NULL) {
				PyErr_SetString(PyExc_SystemError,
					"dynamic module not initialized properly");
				return NULL;
			}
			Py_INCREF(m);
			return Py_BuildValue("S", m);
		}
	}
	return NULL;
}

static PyObject* rootlib_getList(PyObject *self, PyObject *args)
{
	int iTupleSize = 0;
	while (NULL != rootlib_init_methods[iTupleSize].func_name) {iTupleSize++;}

	PyObject* retTuple = PyTuple_New(iTupleSize);
	for (int i = 0; NULL != rootlib_init_methods[i].func_name; i++)
	{
		PyObject* retSubString = PyString_FromString(rootlib_init_methods[i].func_name);
		PyTuple_SetItem(retTuple, i, retSubString);
	}
	return retTuple;
}

void initrootlibManager()
{
	static struct PyMethodDef methods[] =
	{
		{"isExist", rootlib_isExist, METH_VARARGS},
		{"moduleImport", rootlib_moduleImport, METH_VARARGS},
		{"getList", rootlib_getList, METH_VARARGS},
		{NULL, NULL},
	};

	PyObject* m;
	m = Py_InitModule("rootlib", methods);
}
