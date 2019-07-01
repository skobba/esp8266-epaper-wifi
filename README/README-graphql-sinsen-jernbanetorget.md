{
  trip(
    from: {
        place: "NSR:StopPlace:6035"
        name:"Sinsen, Oslo"
    }
    to: {
        place:"NSR:StopPlace:58366"
        name:"Oslo, Oslo"
    }
    numTripPatterns: 3
    minimumTransferTime: 180
    arriveBy: false
  )

  {
    tripPatterns {
      startTime
      duration
      legs {
        line {
          name
        }
      }
    }
  }
}
