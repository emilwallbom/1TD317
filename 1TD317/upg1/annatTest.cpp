#include <iostream>
using namespace std;

int main()
{
  int best_time = INT_MAX; // Initialisera med maximalt värde
  int best_startnummer = 0;
  int total_tavlande = 0;

  while (true)
  {
    int startnummer;
    cout << "Startnummer? ";
    cin >> startnummer;

    if (startnummer < 1)
      break; // Avsluta loopen om startnummer är mindre än 1

    int start_timme, start_minut, start_sekund;
    cout << "Starttid? ";
    cin >> start_timme >> start_minut >> start_sekund;

    int mal_timme, mal_minut, mal_sekund;
    cout << "Måltid? ";
    cin >> mal_timme >> mal_minut >> mal_sekund;

    int delta_timme = mal_timme - start_timme;
    int delta_minut = mal_minut - start_minut;
    int delta_sekund = mal_sekund - start_sekund;

    if (delta_sekund < 0)
    {
      delta_minut--;
      delta_sekund += 60;
    }

    if (delta_minut < 0)
    {
      delta_timme--;
      delta_minut += 60;
    }

    int total_tid = delta_timme * 3600 + delta_minut * 60 + delta_sekund;

    if (total_tid < best_time)
    {
      best_time = total_tid;
      best_startnummer = startnummer;
    }

    total_tavlande++;
  }

  if (total_tavlande > 0)
  {
    int best_tid_timme = best_time / 3600;
    int best_tid_minut = (best_time % 3600) / 60;
    int best_tid_sekund = best_time % 60;

    cout << "Vinnare: Startnummer " << best_startnummer << ", Sluttid: "
         << best_tid_timme << " tim, " << best_tid_minut << " min, " << best_tid_sekund << " sek" << endl;
    cout << "Totalt antal tävlande: " << total_tavlande << endl;
  }
  else
  {
    cout << "Inga tävlande." << endl;
  }

  return 0;
}
