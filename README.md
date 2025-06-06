# Scalatrafo
 Bewertungen von einer Skala in eine andere umrechnen.

Neueste Version: [Herunterladen](https://github.com/Alsweider/Scalatrafo/releases/latest)

![2025-04-10 14_00_42-Scalatrafo v0 2 0](https://github.com/user-attachments/assets/779167e9-b6c5-4577-bfd5-071cd993c012)

Nehmen wir einmal an, Sie sind auf verschiedenen Filmbewertungsportalen unterwegs und denken sich: "Auf IMDb.com habe ich diesen Film mit 7 von 10 Sternen bewertet. Auf Criticker.com gehen die Bewertungen bis 100, also vergebe ich dort 70 von 100 Punkten." Das wäre eine ungenaue Übertragung[^1], denn auf IMDb beginnt die Skala bei 1 und geht bis 10, während Criticker eine Skala von 0 bis 100 ermöglicht. Der Faktor 10 passt also nicht, wenn man erreichen möchte, dass etwa die unterste Bewertungsstufe auf Skala 1 auch der niedrigstmöglichen Bewertung auf Skala 2 entspricht. Um eine genaue Entsprechung der Bewertungen zu ermöglichen, bedient sich dieses Programm einer Formel für die lineare Abbildung.

<a href="https://github.com/Alsweider/Scalatrafo/releases/latest"><img src="https://github.com/Alsweider/Scalatrafo/blob/40f83a5bd0bc30d66a9844fe76dec7f6097312f3/icon.png" alt="Scalatrafo herunterladen" style="width:300px;"></a>

[^1]: Bei Criticker speziell ist das nicht so problematisch, da der [Algorithmus](https://www.criticker.com/explain/) auf Durchschnittswerten der eigenen Bewertungen beruht, womit das Bewertungsschema egal ist, solange man nur durchgängig nach einem konsistenten Muster vorgeht und nicht plötzlich einen anderen Wertebereich verwendet. Auf anderen Plattformen hingegen führen solche Abweichungen leicht zu Verzerrungen und schlechteren Vorschlägen bei den automatischen Empfehlungen. 
