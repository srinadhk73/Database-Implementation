#include "HeapImplementation.h"

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
/* Srinadh Kakkera */

HeapImplementation::HeapImplementation () : file(), curPage(), currPagePtr(0)
{}

HeapImplementation::~HeapImplementation()
{}

int HeapImplementation::Open (const char *f_path)
{
  char *send_path=const_cast<char *>(f_path);
  file.Open(1, send_path);
  this->MoveFirst();
  return 0;
}

int HeapImplementation::Create (const char *f_path, fType f_type, void *startup)
{
  if (heap != f_type){
	  return 1;
  }
  char *send_path=const_cast<char *>(f_path);
  file.Open(0,send_path);
  return 0;
}

void HeapImplementation:: Load (Schema &f_schema, const char *loadpath)
{
  FILE *loadTable = fopen (const_cast<char *>(loadpath), "r");
  if (0 == loadTable)
    exit(-1);
  Record record;
  Page page;
  int recordindex = 0;
  int pageindex = 0;

  while (1 == record.SuckNextRecord (&f_schema, loadTable))
    { // Read Next Record
      if(pageindex <0 || recordindex <0 ){
    	  exit(0);
      }
      recordindex++;
      if (recordindex % 10000 == 0) {
        cerr << recordindex << "\n";
      }
      // Adding Records into page Buffer and when buffer fills,  it is appended into Pages.
      int full = page.Append(&record);
      if (0 == full)
        {
          // page was full
          file.AddPage(&page,pageindex++);
          page.EmptyItOut();
          page.Append(&record);
        }
    }

  { // Add the last page whether it is full or half filled
    file.AddPage(&page,pageindex++);
    cout << "Total Records: " << recordindex << "\n" <<
      " No of Pages: " << pageindex  << endl;
  }

}

void HeapImplementation:: MoveFirst ()
{
  currPagePtr = (off_t) 0;
  if (0 != file.GetLength())
    {
      file.GetPage(&curPage, currPagePtr);
    }
  else
    {
      curPage.EmptyItOut();
    }
}



void HeapImplementation:: Add (Record &rec)
{
  Page tempPage;
  off_t filelength=file.GetLength();
  if (0 != filelength)
    {
      file.GetPage(&tempPage, file.GetLength() - 2 );
      //When the page  is full
      if (0 == tempPage.Append(&rec))
        {

          tempPage.EmptyItOut();
          tempPage.Append(&rec);
          file.AddPage(&tempPage,file.GetLength()-1);
        }
      else  {
          file.AddPage(&tempPage,file.GetLength()-2);
        }
    }
  else
    {
      if (1 == tempPage.Append(&rec))
        {
          file.AddPage(&tempPage,0);
        }
      else   {
          exit(-1);
        }
    }
}

int HeapImplementation:: GetNext (Record &fetchme)
{
  if(0 == curPage.GetFirst(&fetchme))
    {
      currPagePtr += 1;
      off_t filelength=file.GetLength()-1;
      if(currPagePtr + 1 <= filelength){
          file.GetPage(&curPage, currPagePtr);
          assert(1 == curPage.GetFirst(&fetchme));
          return 1;
        }
      else
        {

          return 0;
        }
    }
  else
    {
      return 1;
    }
  return 0;
}



int HeapImplementation:: GetNext (Record &fetchme, CNF &cnf, Record &literal)
{
  ComparisonEngine comparisionvariable;
  while(SUCCESS == this->GetNext(fetchme))
    {
      if (SUCCESS == comparisionvariable.Compare(&fetchme,&literal,&cnf))
        {
          return 1;
        }
      else {
    	  continue;
      }
    }
  return 0;
}

int HeapImplementation:: Close ()
{
  int check = file.Close();
  if (check >= 0)  {
      return 1;
    }
  else
    {
      return 0;
    }
}
