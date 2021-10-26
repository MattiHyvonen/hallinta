#include <Hallinta.hpp>

void Hallinta::lisaaSubjekti(std::weak_ptr<Hallintarajapinta> p) {
  subjektit.push_back(p);
}

void Hallinta::piirraKaikki() {
  suoritaKaikille(HALLINTAFUNKTIO_PIIRRA);
}

void Hallinta::laskeKaikki() {
  suoritaKaikille(HALLINTAFUNKTIO_LASKE);
}

void Hallinta::suoritaKaikille(Hallintafunktiot f) {
  for(auto s : subjektit) {
    std::shared_ptr<Hallintarajapinta> tmpSubjekti {s.lock() };
    if(tmpSubjekti) {
      switch(f) {
        case HALLINTAFUNKTIO_LASKE:
        tmpSubjekti->laske();
        break;
        case HALLINTAFUNKTIO_PIIRRA:
        tmpSubjekti->piirra();
        break;
      }
    }
  }
}
