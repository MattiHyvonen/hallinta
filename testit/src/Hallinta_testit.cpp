#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <Hallintarajapinta.hpp>
#include <Hallinta.hpp>

using ::testing::_;


class Piirto : public Hallintarajapinta {
private:
  std::string kuvaus {};

public:
  const std::string& haeKuvaus() const {
    return kuvaus;
  }

  void piirra() {
    kuvaus = "Piirto: Piirretään";
  }
};


class Laskenta : public Hallintarajapinta {
private:
  std::string kuvaus {};

public:
  const std::string& haeKuvaus() const {
    return kuvaus;
  };

  void piirra() {
    kuvaus = "Laskenta: Odotetaan piirtoa";
  }

  void laske() {
    kuvaus = "Laskenta: Lasketaan";
  }
};


class Hallinta_testit : public ::testing::Test {};

/* Kun lisätään Piirto-tyyppinen subjekti heikon osoittimen kautta
  ja ajetaan Hallinnan Piirra -funktio,
  ajetaan subjektin Piirto-funktio. Tämä testataan seurausten perusteella.
*/
TEST_F(Hallinta_testit, hallintaAjaaSubjektinPiirra_funktion) {
  Hallinta H;
  std::shared_ptr<Piirto> subjekti {new Piirto};
  std::weak_ptr<Piirto> heikkoOsoitinSubjektiin {subjekti};
  H.lisaaSubjekti(heikkoOsoitinSubjektiin);
  H.piirraKaikki();
  ASSERT_EQ(subjekti->haeKuvaus(), "Piirto: Piirretään");
}

/* Sama kuin edellinen, mutta lisätään subjekti shared ptr:n kautta.
  Testataan että toimii samalla tavalla.
*/
TEST_F(Hallinta_testit, weakPtrMuuntoSharedPtristaToimii) {
  Hallinta H;
  std::shared_ptr<Piirto> subjekti {new Piirto};
  H.lisaaSubjekti(subjekti);
  H.piirraKaikki();
  ASSERT_EQ(subjekti->haeKuvaus(), "Piirto: Piirretään");
}

/* Kun lisätään subjekti hallintaan, subjektin use_count pysyy samana */
TEST_F(Hallinta_testit, lisaaSubjektiEiMuutaUseCountia) {
  Hallinta H;
  std::shared_ptr<Piirto> subjekti {new Piirto};
  std::weak_ptr<Piirto> heikkoOsoitinSubjektiin {subjekti};
  ASSERT_EQ(subjekti.use_count(), 1);
  H.lisaaSubjekti(heikkoOsoitinSubjektiin);
  ASSERT_EQ(subjekti.use_count(), 1);
}

/* 2 Piirto-subjektia */
TEST_F(Hallinta_testit, kaksiPiirtosubjektia) {
  Hallinta H;
  std::shared_ptr<Piirto> subjekti0 {new Piirto};
  std::shared_ptr<Piirto> subjekti1 {new Piirto};
  H.lisaaSubjekti(subjekti0);
  H.lisaaSubjekti(subjekti1);
  H.piirraKaikki();
  ASSERT_EQ(subjekti0->haeKuvaus(), "Piirto: Piirretään");
  ASSERT_EQ(subjekti1->haeKuvaus(), "Piirto: Piirretään");
}

/* Subjektin vapauttaminen kun se on lisättynä hallintaan ei aiheuta kaatumista
*/
TEST_F(Hallinta_testit, subjektinVapauttaminenKeskenEiAiheutaKaatumista) {
  Hallinta H;
  std::shared_ptr<Piirto> subjekti {new Piirto};
  H.lisaaSubjekti(subjekti);
  subjekti.reset();
  H.piirraKaikki();
}

/* Kun lisätään Laskenta-tyyppinen subjekti ja ajetaan PiirräKaikki -funktio,
  ajetaan subjektin Piirrä-funktio. Testataan seurausten avulla.
*/
TEST_F(Hallinta_testit, hallintaAjaaLaskentasubjektinPiirra_funktion) {
  Hallinta H;
  std::shared_ptr<Laskenta> subjekti {new Laskenta};
  H.lisaaSubjekti(subjekti);
  H.piirraKaikki();
  ASSERT_EQ(subjekti->haeKuvaus(), "Laskenta: Odotetaan piirtoa");
}

TEST_F(Hallinta_testit, hallintaAjaaLaskentasubjektinLaske_funktion) {
  Hallinta H;
  std::shared_ptr<Laskenta> subjekti {new Laskenta};
  H.lisaaSubjekti(subjekti);
  H.laskeKaikki();
  ASSERT_EQ(subjekti->haeKuvaus(), "Laskenta: Lasketaan");
}

TEST_F( Hallinta_testit,
        ajetaanLaskentojenPiirra_JaLaske_funktiotJaPiirtojenPiirra_funktiot) {
  Hallinta H;
  std::shared_ptr<Laskenta> subjekti_laskenta0 {new Laskenta};
  std::shared_ptr<Laskenta> subjekti_laskenta1 {new Laskenta};
  std::shared_ptr<Piirto> subjekti_piirto {new Piirto};
  H.lisaaSubjekti(subjekti_laskenta0);
  H.lisaaSubjekti(subjekti_laskenta1);
  H.lisaaSubjekti(subjekti_piirto);
  H.laskeKaikki();
  ASSERT_EQ(subjekti_laskenta0->haeKuvaus(), "Laskenta: Lasketaan");
  ASSERT_EQ(subjekti_laskenta1->haeKuvaus(), "Laskenta: Lasketaan");
  ASSERT_EQ(subjekti_piirto->haeKuvaus(), "");
  H.piirraKaikki();
  ASSERT_EQ(subjekti_laskenta0->haeKuvaus(), "Laskenta: Odotetaan piirtoa");
  ASSERT_EQ(subjekti_laskenta1->haeKuvaus(), "Laskenta: Odotetaan piirtoa");
  ASSERT_EQ(subjekti_piirto->haeKuvaus(), "Piirto: Piirretään");
}
