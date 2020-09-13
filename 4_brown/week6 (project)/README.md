# Final project of the Brown belt: Transport catalog

This program stores information about bus stops (name, latitude, longitude), road distances between stop pairs and bus routes (name, route type and sequence of stops). Data input is done using JSON format.

JSON parsing is done in json.h and json.cpp. Those files were given by the course staff, but were substantially modified.

Routing is done via a graph representation of the stops. Corresponding header files are:
- graph.h (graph implementation, written by the course staff, wasn't modified)
- router.h (router implementation, written by the course staff, wasn't modified)
- router_wrapper.h (a wrapper made in order to use general solution (router.h) for this particular task)

Testing is done using a pet unit-test framework (test_runner.h) which was developed as a course assignment.

## Input requests
### Adding bus stop
Example request:

    {
      "type": "Stop",
      "latitude": 55.57914086868687,
      "longitude": 37.58821,
      "name": "Kiyevskoye sh 20",
      "road_distances": {
        "Kiyevskoye sh 50": 645868,
        "Kiyevskoye sh 90": 407045,
        "Troparyovo": 172308
      }
    }
	
### Adding bus route
Example request:

    {
      "type": "Bus",
      "is_roundtrip": false,
      "name": "18",
      "stops": [
        "Vnukovo",
        "Troparyovo",
        "Pr Vernadskogo 10",
        "Leningradskoye sh 50",
        "Leningradskoye sh 100",
        "Khimki",
        "Sheremetyevo"
      ]
    }

## Output requests
### Stop information
Outputs bus routes that run through a given stop.

Example request:

    {
      "type": "Stop",
      "id": 132064624,
      "name": "Komsomolskiy pr 50"
    }
	
Example response:

    {
      "request_id": 132064624,
      "buses": [
        "1",
        "17",
        "43k",
        "51k",
        "81",
        "9k"
      ]
    }

### Bus information
For a given route outputs:
* "stop_count": total number of stops
* "unique_stop_count": total number of unique stops
* "route_length": route length calculated as the sum of road distances between pairs of stops
* "curvature": ratio of previously calculated route length to route length calculated as the sum of flight distances (using latitude and longitude of the stops)

Example request:

    {
      "type": "Bus",
      "id": 1742458421,
      "name": "44"
    }
	
Example response:

    {
      "curvature": 165.6037400615639,
      "request_id": 1742458421,
      "unique_stop_count": 19,
      "stop_count": 37,
      "route_length": 12456424
    }

### Route information
For a given pair of stops output the shortest way (in terms of total time) to get from stop A to stop B.

Example request:

    {
      "type": "Route",
      "id": 1705878213,
      "to": "Mezhdunarodnoye sh 100",
      "from": "Leningradskoye sh 10"
    }

Example response:

    {
      "request_id": 1705878213,
      "total_time": 1290.6242857142856,
      "items": [
        {
          "type": "Wait",
          "stop_name": "Leningradskoye sh 10",
          "time": 490
        },
        {
          "type": "Bus",
          "bus": "94k",
          "span_count": 1,
          "time": 157.6395
        },
        {
          "type": "Wait",
          "stop_name": "Khimki",
          "time": 490
        },
        {
          "type": "Bus",
          "bus": "25k",
          "span_count": 1,
          "time": 152.9847857142857
        }
      ]
    }
