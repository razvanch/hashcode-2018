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
    int start_time;
    int last_time;
};

struct Car {
    int x;
    int y;
    Ride *target;
};

int inline manhattan(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int main()
{
    int n_rows, n_cols, n_fleet, n_rides, bonus, time;

    cin >> n_rows >> n_cols >> n_fleet >> n_rides >> bonus >> time;

    vector<Ride*> rides;

    for (int _ = 0; _ < n_rides; _++)
    {
        Ride *ride = new Ride();

        cin >> ride->x_start >> ride->x_end
            >> ride->y_start >> ride->y_end
            >> ride->start_time >> ride->last_time;

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

        cars.push_back(car);
    }

    // sort(rides.begin(), rides.end(),
    //     [](const Ride* a, const Ride* b) -> bool
    //     {
    //         return a->start_time;
    //     }
    // );


    return 0;
}