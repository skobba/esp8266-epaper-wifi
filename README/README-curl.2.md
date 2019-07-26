# curl - GET
curl 'https://api.entur.io/journey-planner/v2/graphql' -H 'Content-Type: application/json' --data-binary '{"query":"{\ntrip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}¨numTripPatterns:3\nminimumTransferTime:180\narriveBy:false\n)\n\n{\ntripPatterns{\nstartTime\nduration\nlegs{\nline{\nname\n}\n}\n}\n}\n}\n","variables":null}' --compressed

# curl - POST
curl -H "Content-Type: application/json" -X POST -d '{"query":"{\ntrip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}¨numTripPatterns:3\nminimumTransferTime:180\narriveBy:false\n)\n\n{\ntripPatterns{\nstartTime\nduration\nlegs{\nline{\nname\n}\n}\n}\n}\n}\n","variables":null}' https://api.entur.io/journey-planner/v2/graphql -v


POST /journey-planner/v2/graphql HTTP/1.1
Host: api.entur.io
Cache-Control: no-cache
Content-Type: application/json
Content-Length: 2

{}



# view in curl
curl 'https://api.entur.io/journey-planner/v2/graphql' -H 'Content-Type: application/json' --data-binary '{"query":"{\ntrip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}¨numTripPatterns:3\nminimumTransferTime:180\narriveBy:false\n)\n\n{\ntripPatterns{\nstartTime\nduration\nlegs{\nline{\nname\n}\n}\n}\n}\n}\n","variables":null}' -v

curl -v http://testserver.com/post -d "firstname=john&lastname=doe"


curl 'https://reisapi.ruter.no/Place/GetPlaces/grefsen' -H 'Content-Type: application/json'
