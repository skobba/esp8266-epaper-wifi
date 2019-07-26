# Ref
## GraphQL Tool
https://api.entur.io/journey-planner/v2/ide/
## GraphQL API
https://api.entur.io/journey-planner/v2/graphql
Request URL: https://api.entur.io/journey-planner/v2/graphql
Request Method: POST

## Help
https://reisapi.ruter.no/help
## Mon
https://mon.ruter.no/monitor/3012110/T%C3%A5rn%C3%A5sen/
## Find nearby stops
https://en-tur.no/nearby-stop-place-detail?id=NSR:StopPlace:6505



# IDs
## 3012100 - Sinsen [T-bane]
## 3010011 - Jernbanetorget [T-bane]


# Graphql - Sinsen til Jernbanetorget
from: {
    place: "NSR:StopPlace:6035"
    name:"Sinsen, Oslo"
}
to: {
    place:"NSR:StopPlace:58366"
    name:"Oslo, Oslo"
}

# Grefsen Stasjon (tog)
https://reisapi.ruter.no/Place/GetPlaces/grefsen
3012110


### Get the fucking stopps fra STORO
curl https://reisapi.ruter.no/StopVisit/GetDepartures/3012120

https://reisapi.ruter.no/StopVisit/GetDepartures/NSR:StopPlace:6035


### STOP PÅ STORO
curl https://reisapi.ruter.no/line/GetLinesByStopID/3012120

### INFOR OM STORO
https://reisapi.ruter.no/line/GetLinesByStopID/3012120

curl https://reisapi.ruter.no/Trip/GetTrip/{id}?time={time}
curl https://reisapi.ruter.no/Trip/GetTrip/333



curl https://reisapi.ruter.no/Travel/GetTravels?fromPlace=3010011&toPlace=3011324&isafter=0

# all data about a stop
curl https://reisapi.ruter.no/Place/GetStop/3012110

url=http://reisapi.ruter.no/StopVisit/GetDepartures/3011324?datetime=2017-12-19T13:10&transporttypes=Bus&linenames=78B

curl http://reisapi.ruter.no/StopVisit/GetDepartures/3011324ransporttypes=Bus&linenames=78B

Ruter_Skoy.updateInterval=60000


curl https://reisapi.ruter.no/Place/GetStops/333

# Stopid

curl https://reisapi.ruter.no/Place/GetStop/3012110

# Search

curl https://reisapi.ruter.no/

curl https://reisapi.ruter.no/Travel/GetTravels?fromPlace=3012110

curl https://reisapi.ruter.no/Travel/GetTravels?fromPlace=3012110&toPlace=3012112
Travel/GetTravels?fromPlace={fromPlace}&toPlace={toPlace}

curl https://reisapi.ruter.no/Travel/GetTravels?fromPlace=3012112&toPlace=301211


<Place i:type="Stop">
<District>Oslo</District>
<DistrictID i:nil="true"/>
<ID>3012110</ID>
<Name>Grefsen [tog]</Name>
<PlaceType>Stop</PlaceType>
<IsHub>false</IsHub>
<Lines>
<Line>
<ID>9103</ID>
<LineColour>003087</LineColour>
<Name>L3</Name>
<Transportation>Train</Transportation>
</Line>
<Line>
<ID>9130</ID>
<LineColour>003087</LineColour>
<Name>R30</Name>
<Transportation>Train</Transportation>
</Line>
<Line>
<ID>9180</ID>
<LineColour>003087</LineColour>
<Name>R30x</Name>
<Transportation>Train</Transportation>
</Line>