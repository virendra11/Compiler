#include "ParserFunctions.hpp"

vector<string> FirstSet::First (string Gsym, Grammar CFG)
{
 	vector<string> retval;
	int flag = 0;
	// Gsym is a terminal.
	if ( CFG.isTerm.find(Gsym)->second) 
		{
			
			retval.push_back(Gsym);
			FirstSetAddEntry(Gsym, retval);
		}

	//Gsym is a non-teminal.
	/*
		"" Iterator for a map "" 
			is a pointer to the pair(key, value). To access them, we have it->first, it->second. 
			map< string, bool> isTerm,	map<string, vector<string>> firstSet
		"" Iterator for a vector ""
			is a pointer to value that is stored at the position where the iterator is pointing at present. To access it, we have (*it)
			vector<string> matchedRules
	*/
	else
		{
			// We need to search for all productions that start with the non-terminal GSym.
			vector<Rule>::iterator itr;
			vector<string>::iterator its1, its2;
			vector<string> tail, firstvals;
			vector<Rule> matchedRules = CFG.GrammarFindRule(Gsym);	// All Rules whose head starts with Gsym.
			
			for ( itr = matchedRules.begin; itr < matchedRules.end; itr++ )
				{
					// Given a rule, We need to traverse all the symbols in it.
					
					tail = (*itr).tail;	// #TODO This requires tail to be public member.
					// ########################## TRAVERSING A MATCHED RULE #############################################
					// Now we will traverse the tail of the current production chosen to build the first set.
					for ( its1 = tail.begin; its1 < tail.end; its1++ )
						{
							flag = 0;	
							// Hoping the leftmost symbol in the reduction is a terminal or even if it's a non-terminal, it's firstSet does
							// not contain an epsilon. Hence flag is set to 0 in this hope.

							// The condition below states that the leftmost symbol of this reduction is a terminal.
							if ( CFG.isTerm.find(*its1)->second )		// Terminating condition for Recursion.
								retval.push_back(*its1);
							else	// It's a non-terminal.
							{	
							/* This recursive call would also find the FIRST sets of a lot of other grammar symbols as well. So before
							   calling First(Gsym) we need to check whether there alredy exists an entry corresponding to Gsym in firstSet map.
							*/
								if ( this.firstSet.find(*its1) == firstSet.end )
								{	/* It's first set has not been constructed yet and thus a recusive call is required to construct it. */
                                                                        
									// ###  RECURSIVE CALL ###
									First ( *its1 );
				                                        // ### RECURSIVE CALL ###

 									/*  Here we are sure that the recursion will terminate at some point of time; as the base condition
									    is reached. It cannot happen that the recursion encounters a loop. For eg :
									    First ( A ) ==> FIRST( B ) ==> ....	 This sequence will never contain a back edge. 
									    Since if it contains a back edge from a Non-terminal K to Non-terminal T let's say, it implies 
									    that we have a reduction like  ( K --> T ). But from the sequence we are following, we also 
									    have a reduction like  ( T --> K ) as per the recursion path. This implies we can have a reduction
									    T --> T or K --> K in the grammar which implies it is left recursive. Hence contradiction.
									*/
								}	
									
									/* We now have the firstSet for the non-terminal we encountered in the production for Gsym. */
									firstvals = (this.firstSet.find(*its1))->second;
									// firstvals is a vector of strings.
									for ( its2 = firstvals.begin; its < firstvals.end; its++ )
										{
											if ( *its2 == "#" ) 
												// We have an epsilon production, Hence we need to continue in the loop.
												flag = 1;
											else
												{ retval.push_back(*its2); }

										}
							 }
							if ( flag == 0 )	break;	// No epsilon productions found. Else continue.											
						}
					// ########################## TRAVERSING A MATCHED RULE ############################################# 	
				}
		
			FirstSetAddEntry(Gsym, retval);			// Filling the class data structure firstSet through Recursive Calls.
		}
return retval;
}	


vector<string> FollowSet::Follow (string Gsym, Grammar CFG)
{
vector<string> retval;
if ( Gsym == CFG.startSym )
{
	retval.push_back("$");		// We place the "$" symbol in follow of the start symbol.
}



























return retval;
}
