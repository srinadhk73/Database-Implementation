#ifndef HEAP_DBFILE_H
#define HEAP_DBFILE_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"

/* sub class for dbfile impl, supporting linear operations*/

class HeapImplementation
{
  File file;
  Page curPage;
  off_t currPagePtr;

 public:
  HeapImplementation ();
  ~HeapImplementation();
  int Open (const char *fpath);
  int Create (const char *fpath, fType file_type, void *startup);
  int Close ();

  void Load (Schema &myschema, const char *loadpath);

  void MoveFirst ();
  void Add (Record &addme);
  int GetNext (Record &fetchme);
  int GetNext (Record &fetchme, CNF &cnf, Record &literal);
};
#endif




