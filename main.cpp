// ------------- FILE HEADER -------------
// Author ✅:
// Assignment ✅:
// Date ✅:
// Citations:

// Single-Winner Ranked Choice Voting
// This form of voting is also referred to as instant runoff voting (IRV). Single-winner RCV was
// used to elect Portland Mayor and Portland Auditor. Per City of Portland Code, single-winner
// ranked choice voting operates as following:
//  ● Voters may rank up to 6 candidates in order of preference.
//  ● If no candidate receives a majority of the vote (i.e. 50%+1) after counting Rank 1 votes
// for each candidate in the first round, the candidate with the fewest number of votes is
// eliminated and votes for that candidate are transferred to their voters’ next-highest
// ranked active candidates.
//  ○ If a ballot does not indicate any additional candidate rankings, the ballot is
// declared inactive and set aside.
//  ● If a candidate in the second round receives a majority of the votes tallied in that round,
// they are declared elected. If no candidate receives a majority, the process of
// eliminating a candidate and transferring votes in rounds continues

// Multi-Winner Ranked Choice Voting
// This form of voting is also referred to as single transferable vote (STV) or proportional ranked
// choice voting (PRCV). Multi-winner RCV was used for City of Portland City Council elections,
// which elect 3 candidates per district for four newly-created districts. Per City of Portland
// Code, multi-winner ranked choice voting operates as follows:
//  ● Voters rank up to 6 candidates in order of preference.
//  ● The City charter specifies the threshold for election as the percentage of votes a
//
// candidate must receive to be elected such that no more candidates could reach the
// threshold than the number of offices to be elected. In a Portland City Council race with
// three Council members being elected, the threshold is 25%+1 vote.
//  ● After the initial round of counting the Rank 1 votes for each candidate, if one or more
// candidates reach the threshold, they are declared elected. Tabulation continues in
// rounds until all seats to be filled are elected.
//  ○ If a candidate is elected in a round, any votes they received above the threshold
//    (known as surplus votes) are transferred to their voters’ next-ranked remaining
//    candidates. Surplus votes are transferred on a fractional basis to ensure all
//    voters who voted for the elected candidate contribute to the identification of
//    next-ranked candidates.
//    For example, if the threshold were established at 9,000 votes and a
//    candidate received 10,000 votes, their “surplus” is 1,000 votes. The
//    1,000 votes are 10% (0.1) of the total votes for the elected candidate, so
//    0.1 vote is transferred from each of the 10,000 ballots to the next-ranked
//    candidate identified on each respective ballot.
//  ○ In each subsequent round of tabulation, the candidate with the fewest number
//    of votes is eliminated and votes for that candidate are transferred to their voters’
//    next highest-ranked active candidates.
//  ○ If a ballot does not have any remaining valid rankings when a vote is being
//    transferred, the ballot is declared inactive and set aside.

// ------------- CODE -------------
#include <iostream>
#include <list>
#include <map>
#include <limits>

using namespace std;

// Function prototypes (if any)

class Ballot
{
public:
  list<string> ranked_selections;
  void print()
  {
    cout << endl
         << "BALLOT" << endl;
    for (const string s : ranked_selections)
    {
      cout << s << endl;
    }
  }
};

const int MAX_RANK = 6;

enum
{
  START_COUNT,
  END_COUNT,
  START_BALLOT,
  END_BALLOT
};

const string CONTROL_CONSTANTS[] = {"START_COUNT", "END_COUNT", "START_BALLOT", "END_BALLOT"};

// Main function
// https://en.cppreference.com/w/cpp/language/main_function.html
int main()
{
  list<Ballot> ballots;

  string s = "";
  while (cin >> s && s != CONTROL_CONSTANTS[END_COUNT])
  {
    if (s == CONTROL_CONSTANTS[START_BALLOT])
    {
      Ballot ballot;
      int rank = 1;
      while (cin >> s && s != CONTROL_CONSTANTS[END_BALLOT])
      {
        ballot.ranked_selections.push_back(s);
      }
      if (ballot.ranked_selections.size() <= MAX_RANK)
      {
        ballots.push_back(ballot);
      }
      else
      {
        cout << "BALLOT ERROR MAX RANK EXCEEDED" << endl;
      }
      // ballot.print();
    }
  }

  int majority = ballots.size() / 2 + 1;
  bool next = true;

  cout << "NEEDED TO WIN: " << majority << endl;
  do
  {
    map<string, int> votes;
    for (const Ballot &ballot : ballots)
    {
      if (ballot.ranked_selections.size() > 0)
      {
        string selection = ballot.ranked_selections.front();
        if (votes.count(selection) > 0)
        {
          votes[selection]++;
        }
        else
        {
          votes[selection] = 1;
        }
        if (votes[selection] >= majority)
        {
          cout << "WINNER: " << selection << "\tVOTES: " << votes[selection] << endl;
          next = false;
        }
        // cout << selection << '\t' << votes[selection] << endl;
      }
    }
    
    if (next)
    {
      int min = votes.begin()->second;
      string least_votes = votes.begin()->first;
      cout << "INITIAL MIN: " << least_votes << '\t' << min << endl;
      for (const pair<const string, int> &entry : votes)
      {
        const string &key = entry.first;
        const int &value = entry.second;
        cout << key << ": " << value << endl;
        if (value < min)
        {
          min = value;
          least_votes = key;
          cout << "UPDATE MIN: " << least_votes << '\t' << min << endl;
        }
      }
      cout << "ELIMINATING: " << least_votes << '\t' << min << endl;
      for (Ballot &ballot : ballots)
      {
        list<string> &v = ballot.ranked_selections;
        if (v.size() > 0 && v.front() == least_votes)
        {
          cout << "BEFORE erase: " << v.front() << endl;
          v.erase(v.begin());
          if(v.size() > 0) {
            cout << "AFTER erase: " << v.front() << endl;
          }
        }
      }
    }
    //next = false;
  } while (next);

  return 0;
}

// Function implementations (if any)

// ------------- DESIGN -------------
/*
Program Name:

Program Description:

Design:
A. INPUT
Define the input variables including name data type.

B. OUTPUT
Define the output variables including data types.

C. CALCULATIONS
Describe calculations used by algorithms in step D.
List all formulas.
If there are no calculations needed, state there are no calculations.

D. LOGIC and ALGORITHMS
Design the logic of your program using pseudocode or flowcharts.
Use conditionals, loops, functions or array constructs.
List the steps in transforming inputs into outputs.
https://github.com/Glen-Sasek-PCC-Instructor/2025-06-22/blob/main/Pseudocode-Reference.txt


SAMPLE RUNS
Copy from assignment document.

Charlie
END_BALLOT
START_BALLOT
Dylan
Isla
Hannah
Yara
Fiona
Jack
END_BALLOT
START_BALLOT
Olivia
Noah
Xavier
END_BALLOT
START_BALLOT
Michael
Theo
Ethan
Charlie
Quincy
END_BALLOT
START_BALLOT
Zoe
Sam
END_BALLOT
START_BALLOT
Oliver
END_BALLOT
START_BALLOT
Yara
END_BALLOT
START_BALLOT
Dylan
Olivia
Xavier

*/
