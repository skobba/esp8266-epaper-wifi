# Ref
https://www.hjemmeautomasjon.no/forums/topic/4338-script-enturvb-f%C3%A5-inn-data-fra-entur/
https://www.youtube.com/watch?v=Wm1xKj4bKsY

Vel og bra! :) Nå vet vi at busstoppet ved Tasta Senter heter "NSR:StopPlace:28163". Men et busstopp kan faktisk ha flere plattformer, f.eks. en på hver side av veien. Det heter visst "Quay" på engelsk.

"NSR:StopPlace:28163" 

# Quay 
quay(id: String!): Quay


          "destinationDisplay": {
            "frontText": "Sognsvann via Tøyen"
          },
          "quay": {
            "id": "NSR:Quay:11078"
          },

Jepp! Riktig! Altså kan vi filtrere på "NSR:Quay:48449" for å finne avganger fra "NSR:StopPlace:28163" som kun går mot Stavanger.

query {
  quay(id: "NSR:Quay:11078") {
    id
    lines {
      id
    }
  }
}