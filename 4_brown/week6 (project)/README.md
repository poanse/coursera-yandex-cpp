# Transport catalog

Final project of the Brown belt.

This program stores information about bus stops (name, latitude, longitude), road distances between stop pairs and bus routes (name, route type and sequence of stops). Data input is done via json requests:

Example request for adding bus stop:
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

Example request for adding bus route:
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

Additionally following requests are supported:

- Stop. Outputs bus routes that run through a given stop)

Request:
	{
		"type": "Stop",
		"id": 132064624,
		"name": "Komsomolskiy pr 50"
	}
Response:
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

- Bus. For a given route outputs:
* total number of stops
* number of unique stops
* route length calculated as the sum of road distances between stops
* curvature which is ratio of previously calculated route length to route length calculated as the sum of flight distances (using latitude and longitude of the stops)

Request:
	{
		"type": "Bus",
		"id": 1742458421,
		"name": "44"
	}
Response:
  {
    "curvature": 165.6037400615639,
    "request_id": 1742458421,
    "unique_stop_count": 19,
    "stop_count": 37,
    "route_length": 12456424
  }

-Route. For a given pair of stops output the shortest way (in terms of total time) to get from stop A to stop B.

Request:
	{
		"type": "Route",
		"id": 2128614664,
		"to": "Ostozhenka 50",
		"from": "Tverskaya ul 90"
	}
Response:
  {
    "request_id": 2128614664,
    "total_time": 816.7741428571428,
    "items": [
      {
        "type": "Wait",
        "stop_name": "Tverskaya ul 90",
        "time": 490
      },
      {
        "type": "Bus",
        "bus": "22k",
        "span_count": 5,
        "time": 326.77414285714286
      }
    ]
  }

Routing is done via a graph representation of the stops. Corresponding header files are:
- graph.h (graph implementation, written by the course staff, wasn't changed)
- router.h (router implementation, written by the course staff, wasn't changed)
- router_wrapper.h (a wrapper made in order to use general solution (router.h) for this particular task)

Json parsing is done in json.h and json.cpp. Those files were given by the course staff, but were substantially modified.

Testing is done using a pet unit-test framework which was developed as a course assignment.
