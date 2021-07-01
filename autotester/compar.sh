#/bin/bash

cd "$(dirname "$0")"

echo
echo "Ce script compare l'output de projet19 à l'output de demo."
echo "Des images ppm du resultat sont egalement crées, afin de permettre un examen manuel des différences d'execution entre le programme demo et le votre."
echo

nb_e=6
nb_wrong=0
if [ ! -f ../demo ]; then
    echo "Etes-vous sur d'avoir bien placé le dossier test_output dans le meme dossier contenant demo et votre programme compilé sous le nom projet19?"
		echo "La hierarchie doit etre : <dossier contenant demo et projet19>/test_output/compar.sh"
    echo "Pour plus d'information, lire INSTRUCTION.pdf"
		exit 1
fi
if [ ! -f ../projet19 ]; then
    echo "Etes-vous sur d'avoir bien placé le dossier test_output dans le meme dossier contenant demo et votre programme compilé sous le nom projet19?"
		echo "La hierarchie doit etre : <dossier contenant demo et projet19>/test_output/compar.sh"
    echo "Pour plus d'information, lire INSTRUCTION.pdf"
		exit 1
fi

for i in `seq 1 $nb_e`
do
	if [ $i -lt 10 ]
	then
		./../demo < E0$i.txt > output$i.demo.ppm
		./../projet19 < E0$i.txt > output$i.projet19.ppm
	else
		./../demo < E0$i.txt > output$i.demo.ppm
		./../projet19 < E0$i.txt > output$i.projet19.ppm
	fi

  tr -d '\n' <output$i.demo.ppm >output$i.demo.txt
  tr -d '\n' <output$i.projet19.ppm> output$i.projet19.txt
  diff -Z -w -B -E -b -q -s --strip-trailing-cr output$i.demo.txt output$i.projet19.txt

	echo
	rm output$i.demo.txt output$i.projet19.txt
done


  echo "Attention, meme si l'output est identique, il faut egalement s'assurer que les images résultantes s'affichent de manière correcte : ce script ne détecte entre autre pas s'il manque des espaces entre caractères."




# Caporal X
