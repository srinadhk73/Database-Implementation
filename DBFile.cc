#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>

// stub file .. replace it with your own DBFile.cc

DBFile::DBFile () : dbf (NULL){

}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {


	{
			string metafileName;
			char *c_string=(metafileName.append(f_path).append(".meta")).c_str();
		    ofstream metafile;
		    metafile.open(c_string);
		    if(!metafile) return 1;
		    metafile << f_type << endl; // write db type
		    if(!metafile) return 1;
		    metafile.close();
		    dbf = new HeapImplementation();
	}
	return this->dbf->Create(f_path, f_type, startup);


}

void DBFile::Load (Schema &f_schema, const char *loadpath) {

	this->dbf->Load(f_schema,loadpath);
}

int DBFile::Open (const char *f_path) {

	{
			string metafileName;
		    char *c_string=(metafileName.append(f_path).append(".meta")).c_str();
		    ifstream metafile;
		    metafile.open(c_string);
		    if(!metafile) return 1;
		    metafile.close();

		  cout << "Heap Type of File Opened Successfully" << endl;
	      dbf = new HeapImplementation();
	}

	      return this->dbf->Open(f_path);
}

void DBFile::MoveFirst () {
	this->dbf->MoveFirst();
}

int DBFile::Close () {
	if (dbf==NULL){
		return 0;
	}
	int returnvalue = this->dbf->Close();
	  delete dbf;
	  return returnvalue;
}

void DBFile::Add (Record &rec) {
	this->dbf->Add(rec);
}

int DBFile::GetNext (Record &fetchme) {
	return this->dbf->GetNext(fetchme);
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
	return this->dbf->GetNext(fetchme, cnf, literal);
}
