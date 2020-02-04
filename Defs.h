#ifndef DEFS_H
#define DEFS_H


#define MAX_ANDS 20
#define MAX_ORS 20

#define PAGE_SIZE 131072

typedef enum {heap, sorted, tree} fType;
enum Target {Left, Right, Literal};
enum CompOperator {LessThan, GreaterThan, Equals};
enum Type {Int, Double, String};
enum ReturnState {FAILURE = 0, SUCCESS = 1};


unsigned int Random_Generate();


#endif

