#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

#define INF     10000000000

struct Ride {
    int x_start;
    int x_end;
    int y_start;
    int y_end;
    int dist;
    int start_time;
    int last_time;
    int index;
};

struct Car {
    int x;
    int y;
    Ride *target;
    int available_at;
    vector<int> assigned;
};

int n_rows, n_cols, n_fleet, n_rides, bonus, total_time;

int inline manhattan(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

double score_for(Car *car, Ride *ride)
{
    int to_ride = manhattan(car->x, car->y, ride->x_start, ride->x_end);
    int t_start = max(car->available_at + to_ride, ride->start_time);
    int score = 0;

    if (t_start + ride->dist >= ride->last_time)
        return -INF;

    return ride->dist + t_start == ride->start_time ? bonus : 0;
    // return -ride->start_time;
    // return ride->dist - (t_start - car->available_at - to_ride);
    // return -to_ride;
}

int ride_finish(Car *car, Ride *ride)
{
    int to_ride = manhattan(car->x, car->y, ride->x_start, ride->x_end);
    int t_start = max(car->available_at + to_ride, ride->start_time);

    return t_start + ride->dist;
}

int main()
{

    cin >> n_rows >> n_cols >> n_fleet >> n_rides >> bonus >> total_time;

    vector<Ride*> rides;

    for (int i = 0; i < n_rides; i++)
    {
        Ride *ride = new Ride();

        cin >> ride->x_start >> ride->x_end
            >> ride->y_start >> ride->y_end
            >> ride->start_time >> ride->last_time;

        ride->dist = manhattan(ride->x_start, ride->y_start, ride->x_end, ride->y_end);
        ride->index = i;

        rides.push_back(ride);
    }

    vector<Ride*> initials = rides;

    vector<Car*> cars;
    priority_queue<Car *> pq;

    for (int _ = 0; _ < n_fleet; _++)
    {
        Car *car = new Car();

        car->x = 0;
        car->y = 0;
        car->target = nullptr;
        car->available_at = 0;

        cars.push_back(car);
    }

    bool still_good = true;

    while (still_good)
    {
        still_good = false;

        for (Car *car: cars)
        {
            if (car->available_at > total_time)
                continue;

            Ride *best_ride = nullptr;
            double best_score = -INF;

            for (Ride *ride : rides)
            {
                if (ride->index < 0)
                    continue;

                double score = score_for(car, ride);

                if (score > best_score)
                {
                    best_score = score;
                    best_ride = ride;
                }
            }
            
            if (!best_ride)
                continue;

            still_good = true;

            car->assigned.push_back(best_ride->index);

            car->available_at = ride_finish(car, best_ride);
            car->x = best_ride->x_end;
            car->y = best_ride->y_end;

            best_ride->index = -1;
        }        
    }

    double total;

    for (Car *car: cars)
    {
        total += car->assigned.size();

        cout << car->assigned.size();

        for (int ride: car->assigned)
            cout << ' ' << ride;

        cout << '\n';
    }

    // for (Car *car: cars)
    // {
    //     for (int i: car->assigned)
    //     {
    //         cerr << "(" << initials[i]->start_time << ", " << initials[i]->start_time + initials[i]->dist << ", " << initials[i]->last_time << "), ";
    //     }

    //     cerr << '\n';
    // }

    cerr << total / n_rides << '\n';

    return 0;
}