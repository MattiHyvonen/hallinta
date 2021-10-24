#include <Hallinta.hpp>

void Hallinta::lisaaSubjekti(std::weak_ptr<Hallintarajapinta> p) {
  subjektit.push_back(p);
}

void Hallinta::piirraKaikki() {
  for(auto s : subjektit) {
    /* Yritetään tehdä weak pointerista väliaikainen shared pointer. Jos
      onnistuu, ts. jos weak pointer on validi, ajetaan sen kautta subjektin
      funktio.
    */
    if(std::shared_ptr<Hallintarajapinta> tmpSubjekti = s.lock()) {
      tmpSubjekti->piirra();
    }
  }
}

//TODO: vähennettävä toistoa. Ks. piirraKaikki()
void Hallinta::laskeKaikki() {
  for(auto s : subjektit) {
    if(std::shared_ptr<Hallintarajapinta> tmpSubjekti = s.lock()) {
      tmpSubjekti->laske();
    }
  }
}
