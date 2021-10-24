# Hallintaluokka jolla voi lähettää viestejä ohjelman osille

Tällaista voisi käyttää esimerkiksi pelissä.

Ratkaisu muistuttaa "observer design patternia". Viestinsaajat on observerilla weak pointtereilla, ettei niiden tuhoutuminen aiheuttaisi ongelmia.

Tässä repositoriossa on src/main.cpp:ssä käyttöesimerkki ja testit/src:ssä gtest-testit, jotka havainnollistavat miten luokkaa on tarkoitus käyttää.
