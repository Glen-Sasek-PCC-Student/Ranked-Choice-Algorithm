#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

const int MAX_RANK = 10;

const string START_COUNT = "START_COUNT";
const string END_COUNT = "END_COUNT";
const string START_BALLOT = "START_BALLOT";
const string END_BALLOT = "END_BALLOT";

struct Ballot
{
  list<string> ranked_selections;
};

int main()
{
  list<Ballot> ballots;
  string token;

  while (cin >> token && token != END_COUNT)
  {
    if (token == START_BALLOT)
    {
      Ballot ballot;
      while (cin >> token && token != END_BALLOT)
      {
        ballot.ranked_selections.push_back(token);
      }

      if (ballot.ranked_selections.size() <= MAX_RANK)
      {
        ballots.push_back(ballot);
      }
      else
      {
        cout << "BALLOT ERROR MAX RANK EXCEEDED" << endl;
      }
    }
  }

  if (ballots.empty())
  {
    cout << "NO BALLOTS TO COUNT" << endl;
    return 0;
  }

  const int majority = static_cast<int>(ballots.size() / 2) + 1;
  bool continue_tabulation = true;
  string winner = "";

  while (continue_tabulation)
  {
    map<string, int> tally;
    for (const Ballot &ballot : ballots)
    {
      if (!ballot.ranked_selections.empty())
      {
        const string candidate = ballot.ranked_selections.front();
        if (tally.count(candidate) > 0)
        {
          tally[candidate]++;
        }
        else
        {
          tally[candidate] = 1;
        }
      }
    }

    if (tally.empty())
    {
      break;
    }

    for (const pair<const string, int> &entry : tally)
    {
      cout << entry.first << "\tVOTES: " << entry.second << endl;
      if (entry.second >= majority)
      {
        winner = entry.first;
        cout << "WINNER: " << winner << "\tVOTES: " << entry.second << endl;
        continue_tabulation = false;
        break;
      }
    }

    if (!continue_tabulation)
    {
      break;
    }

    string least_candidate = tally.begin()->first;
    int least_votes = tally.begin()->second;

    for (const pair<const string, int> &entry : tally)
    {
      if (entry.second < least_votes)
      {
        least_votes = entry.second;
      }
    }

    cout << "ELIMINATING candidates with: " << least_votes << endl;

    for (Ballot &ballot : ballots)
    {
      if (!ballot.ranked_selections.empty() && tally[ballot.ranked_selections.front()] == least_votes)
      {
        ballot.ranked_selections.pop_front();
      }
    }

    bool active_ballots_remain = false;
    for (const Ballot &ballot : ballots)
    {
      if (!ballot.ranked_selections.empty())
      {
        active_ballots_remain = true;
        break;
      }
    }

    if (!active_ballots_remain)
    {
      cout << "NO ACTIVE BALLOTS REMAIN" << endl;
      break;
    }
  }

  if (winner.empty())
  {
    cout << "NO WINNER DETECTED" << endl;
  }

  return 0;
}
