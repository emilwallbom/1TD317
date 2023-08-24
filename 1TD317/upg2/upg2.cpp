#include <iostream>
using namespace std;

int main()
{
    int leader_time = INT32_MAX;
    int leader = 0;
    int contestant_count = 0;
    while (true)
    {
        int new_contestant;

        cout << "Startnummer? ";
        cin >> new_contestant;

        if (new_contestant < 0)
            break;

        contestant_count++;
        int start_h, start_m, start_s;
        cout << "Starttid? ";
        cin >> start_h >> start_m >> start_s;

        int end_h, end_m, end_s;
        cout << "Sluttid? ";
        cin >> end_h >> end_m >> end_s;
        int delta_h = end_h - start_h;
        int delta_m = end_m - start_m;
        int delta_s = end_s - start_s;

        if (delta_s < 0)
        {
            delta_m--;
            delta_s += 60;
        }

        if (delta_m < 0)
        {
            delta_h--;
            delta_m += 60;
        }

        if (delta_h < 0)
        {
            delta_h += 24;
        }

        int new_contestant_time;
        new_contestant_time = delta_h * 3600 + delta_m * 60 + delta_s;

        if (new_contestant_time < leader_time)
        {
            leader = new_contestant;
            leader_time = new_contestant_time;
        }
    }
    if (contestant_count > 0)
    {
        int leader_h = leader_time / 3600;
        int leader_m = (leader_time % 3600) / 60;
        int leader_s = leader_time % 60;
        cout
            << "Vinnare är startnr: " << leader << endl;
        cout << "Tim: " << leader_h << " Min: " << leader_m << " Sek: " << leader_s << endl;
        cout << "Antal tävlande: " << contestant_count << endl;
    }
    else
    {
        cout << "Inga tävlande" << endl;
    }
    cout << "Programmet avslutas" << endl;
    return 0;
}
