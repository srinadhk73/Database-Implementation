/*
 * GTest.cc
 *
 *  Created on: Feb 3, 2020
 *      Author: srinadhk7373
 */


/*
 * AllTests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: srinivas
 */
//#include "DBTests.cc"

#include <gtest/gtest.h>
#include "DBFile.h"
#include "test.h"



// make sure that the file path/dir information below is correct

const char *dbfile_dir = "binaryfiles"; // dir where binary heap files should be stored
const char *tpch_dir ="/home/srinadhk7373/Desktop/DBI/P1/git/tpch-dbgen/"; // dir where dbgen tpch files (extension *.tbl) can be found
const char *catalog_path = "catalog"; // full path of the catalog file



relation *rel;

TEST(DBFileTest, Create_Equal) {

	DBFile dbfile;
	ASSERT_EQ(0, dbfile.Create( n->path(), heap, NULL));
}



 TEST(DBFileTest, Create_NotEqual) {

     DBFile dbfile;
     EXPECT_EXIT( dbfile.Create( "", heap, NULL), ::testing::ExitedWithCode(1), "BAD.*");
 }



TEST(DBFileTest, Open_Equal) {

	DBFile dbfile;
	ASSERT_EQ(0, dbfile.Open( n->path()) );
}

TEST(DBFileTest, Open_NotEqual) {

	DBFile dbfile;
	ASSERT_EQ(1, dbfile.Open("random__open_file.bin"));
}



TEST(DBFileTest, Close_nation_DBFile) {

	DBFile dbfile;

	dbfile.Create( n->path(), heap, NULL);

	char tbl_path[100]; // construct path of the tpch flat text file
	sprintf (tbl_path, "%s%s.tbl", tpch_dir, n->name());

	dbfile.Load (*(n->schema ()), tbl_path);

	ASSERT_EQ(1, dbfile.Close());

}


TEST(DBFileTest, Close_Empty_File) {

	DBFile dbfile;
	ASSERT_EQ(0, dbfile.Close());

}



int main(int argc, char **argv) {

	setup (catalog_path, dbfile_dir, tpch_dir);

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}




