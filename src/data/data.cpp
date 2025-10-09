#include "./data/data.h"

// Définition du tableau
Question quiz[] = {
  { 
    "Que doit-on à Nostradamus ?",
    { "La prophétie du 11 Septembre",
      "La date de la fin du monde",
      "La prédiction du réchauffement climatique",
      "Le premier livre de recettes sur les confitures"
    },
    'D'
  },
  { 
    "Quelle fête païenne est à l'origine d'Halloween ?",
    { "Samain",
      "Beltane",
      "Yule",
      "Imbolc"
    },
    'A'
  },
  { 
    "Laquelle de ces villes est située en Allemagne ?",
    { "Aix‑la‑Chapelle",
      "Souffelweyersheim",
      "Vitry‑le‑François",
      "Saint‑Amour"
    },
    'A'
  },
  { 
    "Quel animal tue le plus d’hommes chaque année ?",
    { "Le chien (25 000 personnes environ)",
      "La tique",
      "L’hippopotame (500 personnes par an)",
      "Le moustique (725 000 à 1 000 000 personnes environ)"
    },
    'D'
  },
  { 
    "Quel est le pourcentage de population d’animaux sauvages ayant disparu en 50 ans ?",
    { "73%",
      "50%",
      "25%",
      "90%"
    },
    'A'
  },
  { 
    "Quel Grand Ancien de Lovecraft est surnommé “le chaos rampant” ?",
    { "Cthulhu",
      "Nyarlathotep",
      "Shub Niggurath",
      "Yog Sothoth"
    },
    'B'
  },
  { 
    "Qu’est‑ce que la Biéramicine ?",
    { "Une pratique alliant bière et médecine",
      "Une technique de brassage visant à faire des bières sans alcool",
      "La science de la bière",
      "Une religion congolaise faite de foi et de bière"
    },
    'D'
  },
  { 
    "Dans quelle ville allemande peut-on voir la porte de Brandebourg ?",
    { "Munich",
      "Berlin",
      "Hambourg",
      "Cologne"
    },
    'B'
  },
  { 
    "Quand le Soleil disparaîtra‑t‑il, absorbant Mercure, Vénus et la Terre ?",
    { "Dans moins de 2000 ans",
      "Dans 500 000 ans",
      "Dans plusieurs milliards d’années",
      "On ne sait pas, ce sera la surprise !"
    },
    'C'
  },
  { 
    "Quelle dynastie a été fondée par Henri IV en France ?",
    { "Les Valois",
      "Les Capétiens",
      "Les Carolingiens",
      "Les Bourbons"
    },
    'D'
  }
,
  {
    "De quelle couleur est la fourrure des ours polaires ?",
    {
      "Blanche",
      "Jaune",
      "Noire",
      "Transparente"
    },
    'D'
  },
  {
    "Quel joueur est le dernier français à avoir remporté le tournoi de Roland-Garros ?",
    {
      "Henri Leconte",
      "Richard Gasquet",
      "Gaël Monfils",
      "Yannick Noah"
    },
    'D'
  },
  {
    "Laquelle de ces devises de pays est fausse ?",
    {
      "Suisse, Un pour tous, Tous pour un !!!",
      "Porto Rico, Jean est son nom",
      "Andorre Touche moi si tu l’oses !",
      "Espagne, Toujours plus loin, toujours plus haut, toujours plus fort"
    },
    'C'
  },
  {
    "Quelle mesure n’est pas issue du Front Populaire de 1936 ?",
    {
      "Les Congés payés",
      "La création de l’arrêt maladie",
      "La réduction du temps de travail",
      "L’établissement de conventions collectives"
    },
    'B'
  },
  {
    "\"Pigeon, oiseau à la grise robe...\" : quel acteur déclame ce poème ?",
    {
      "Jean Dujardin",
      "Jean Reno",
      "Benoît Poelvoorde",
      "Gérard Depardieu"
    },
    'C'
  },
  {
    "Qu’est-ce que la mysophobie ?",
    {
      "La peur des germes",
      "La peur des misogynes",
      "La peur de la soupe",
      "La peur de l’eau"
    },
    'A'
  },
  {
    "Quels éléments sont présents à 7 reprises sur le drapeau du Portugal ?",
    {
      "Des épées",
      "Des châteaux",
      "Des pièces de monnaie",
      "Des étoiles"
    },
    'B'
  },
  {
    "En quelle année la France a-t-elle aboli la peine de mort ?",
    {
      "1975",
      "1981",
      "1986",
      "1990"
    },
    'B'
  },
  {
    "Un président des USA a été porté disparu. Pourquoi ?",
    {
      "Il était parti à la pêche",
      "Il faisait un burn out",
      "Il s’est fait kidnapper",
      "Il était parti boire des coups à Las Vegas"
    },
    'A'
  },
  {
    "Quel cépage complète le pinot noir et le pinot meunier pour faire du champagne ?",
    {
      "Merlot",
      "Viognier",
      "Sauvignon",
      "Chardonnay"
    },
    'D'
  },
  {
    "Qui a écrit les paroles de la chanson « Allumer le feu » ?",
    {
      "Zazie",
      "Sylvie Vartan",
      "Lara Fabian",
      "France Gall"
    },
    'A'
  },
  {
    "Quelle ville japonaise était l’ancienne capitale impériale du Japon ?",
    {
      "Tokyo",
      "Kobe",
      "Kyoto",
      "Osaka"
    },
    'C'
  },
  {
    "Quel est le principal organe permettant d’éliminer les toxines du corps ?",
    {
      "La rate",
      "Le pancréas",
      "La vésicule biliaire",
      "Le foie"
    },
    'D'
  },
  {
    "Qu’a fait George Lucas lors de la sortie de Star Wars ?",
    {
      "Il s’est barré à Hawaï",
      "Il a cédé les droits de merchandising",
      "Il a voulu changer de nom",
      "Il a ouvert un restaurant d’ailes de poulet"
    },
    'A'
  },
  {
    "Quel fruit est le plus consommé au monde ?",
    {
      "La banane",
      "La pomme",
      "La mangue",
      "Le fruit du dragon"
    },
    'A'
  },
  {
    "Quelle ville mexicaine est à la frontière près de San Diego ?",
    {
      "Chihuahua",
      "Veracruz",
      "Tijuana",
      "Acapulco"
    },
    'C'
  },
  {
    "Comment s'appelle l'âne dans Shrek ?",
    {
      "Bob",
      "Bill",
      "Jo",
      "Peter"
    },
    'A'
  },
  {
    "Quel est l’hymne de la Légion Étrangère française ?",
    {
      "« Tiens Tiens voilà du boudin »",
      "« Il est des noooootres… »",
      "« 1km à pieds, ça use… »",
      "« Moi, si j’étais un homme… »"
    },
    'A'
  }

};


// Nombre de questions
int nbQuestions = sizeof(quiz)/sizeof(quiz[0]);
