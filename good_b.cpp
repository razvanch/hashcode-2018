#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;


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

int score_for(Car *car, Ride *ride)
{
    int to_ride = manhattan(car->x, car->y, ride->x_start, ride->x_end);
    int t_start = max(car->available_at + to_ride, ride->start_time);
    int score = 0;

    if (t_start + ride->dist > ride->last_time)
        return -100000000;

    if (t_start == ride->start_time)
        score += bonus;

    if (t_start + ride->dist <= ride->last_time)
        score += ride->dist;

    // return score;
    // score -= t_start - car->available_at - to_ride;

    return -car->available_at;
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

    sort(rides.begin(), rides.end(),
        [](const Ride* a, const Ride* b) -> bool
        {
            return a->start_time < b->start_time;
        }
    );

    for (auto ride : rides)
    {
        Car *best_car = nullptr;
        int best_score = -1000000;

        for (Car* candidate: cars)
        {
            int score = score_for(candidate, ride);

            if (score > best_score) {
                best_car = candidate;
                best_score = score;
            }
        }

        if (best_car != nullptr) {
            best_car->assigned.push_back(ride->index);
            best_car->available_at = ride_finish(best_car, ride);

            best_car->x = ride->x_end;
            best_car->y = ride->y_end;
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

    cerr << total / n_rides << '\n';

    return 0;
}