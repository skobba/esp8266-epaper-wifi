{
    "query":"{bikeRentalStationsByBbox(minimumLatitude:59.9 maximumLatitude:60 minimumLongitude:10.7 maximumLongitude:10.8){id name bikesAvailable spacesAvailable}}","variables":null
}


"{\"query\":\"
{bikeRentalStationsByBbox(minimumLatitude:59.9\\nmaximumLatitude:60\\nminimumLongitude:10.7\\nmaximumLongitude:10.8\\n)\\n{id\\nname\\nbikesAvailable\\nspacesAvailable}

}\",\"variables\":null}";



{
    "query":"{bikeRentalStationsByBbox(minimumLatitude:59.9 maximumLatitude:60 minimumLongitude:10.7 maximumLongitude:10.8){id name bikesAvailable spacesAvailable}}","variables":null
}


{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"numTripPatterns:3\\nminimumTransferTime:180\\narriveBy:false){tripPatterns{startTimeduration\\nlegs{line{name}}}}}