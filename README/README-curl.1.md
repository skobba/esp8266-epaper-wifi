--data-binary 


'{"query":"{\ntrip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}¨numTripPatterns:3\nminimumTransferTime:180\narriveBy:false\n)\n\n{\ntripPatterns{\nstartTime\nduration\nlegs{\nline{\nname\n}\n}\n}\n}\n}\n","variables":null}'







--data-binary '{"query":"{\n  trip(from: {place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"} ¨numTripPatterns: 3\n    minimumTransferTime: 180\n    arriveBy: false\n  )\n\n  {\n    tripPatterns {\n      startTime\n      duration\n      legs {\n        line {\n          name\n        }\n      }\n    }\n  }\n}\n","variables":null}'