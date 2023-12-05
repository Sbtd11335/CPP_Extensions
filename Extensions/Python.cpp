#include "Python.hpp"



namespace Extensions{
	namespace Python {
		//Python class
		Python::Python()
		{
			if (Py_IsInitialized() == false)Py_Initialize();
			Main = PyImport_AddModule("__main__");
		}
		Python::Python(int I)
		{
			if (Py_IsInitialized() == false)Py_InitializeEx(I);
		}
		Python::~Python() { Py_Finalize(); }
		void Python::Import(const char* Name) { PyRun_SimpleString((std::string("import ") + Name).c_str()); return; }
		void Python::Run(const char* Code) { PyRun_SimpleString(Code); return; }
		template<> int Python::Get(const char* Variable)
		{
			PyObject* GetObject{ PyObject_GetAttrString(Main, Variable) };
			return PyLong_AsInt(GetObject);
		}
		template<> double Python::Get(const char* Variable)
		{
			PyObject* GetObject{ PyObject_GetAttrString(Main, Variable) };
			return PyFloat_AsDouble(GetObject);
		}
		template<> float Python::Get(const char* Variable)
		{
			PyObject* GetObject{ PyObject_GetAttrString(Main, Variable) };
			return (float)PyFloat_AsDouble(GetObject);
		}
		template<> const char* Python::Get(const char* Variable)
		{
			PyObject* GetObject{ PyObject_GetAttrString(Main, Variable) };
			return PyUnicode_AsUTF8(GetObject);
		}
		//Method
		void pipinstall(const char* Name) { system((std::string("pip install ") + Name).c_str()); return; }
		void Version() { system((std::string("Python --version")).c_str()); return; }
	}

}//Extensions