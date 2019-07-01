
# Welcome to GraphiQL
##################
# GraphiQL is an in-browser IDE for writing, validating, and
# testing GraphQL queries.
#
# Type queries into this side of the screen, and you will
# see intelligent typeaheads aware of the current GraphQL type schema and
# live syntax and validation errors highlighted within the text.
#
# To bring up the auto-complete at any point, just press Ctrl-Space.
#
# Press the run button above, or Cmd-Enter to execute the query, and the result
# will appear in the pane to the right.
#
#
################## Example query for planning a journey
#### Arguments
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
    dateTime: "2019-07-01T23:30:10.018+02:00"
    minimumTransferTime: 180
    arriveBy: false
  )

#### Requested fields
  {
    tripPatterns {
      startTime
      duration
      walkDistance
      legs {
        mode
        distance
        line {
          name
          id
          publicCode
        }
        pointsOnLink {
          points
          length
        }
      }
    }
  }
}
