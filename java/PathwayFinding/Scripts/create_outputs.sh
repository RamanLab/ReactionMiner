
FILES="signs/*"

for f in $FILES
do
  echo "Processing $f file..."

  x=(${f//.dot/ })
  y=(${x//// })
  name=${y[1]}
  echo $name
  dot -Tpng $f > "signs_imgs/"$name".png"
  # take action on each file. $f store current file name
done


FILES="valid_signs/*"

for f in $FILES
do
  echo "Processing $f file..."

  x=(${f//.dot/ })
  y=(${x//// })
  name=${y[1]}
  echo $name
  dot -Tpng $f > "valid_signs_imgs/"$name".png"
  # take action on each file. $f store current file name
done


FILES="rules/*"

for f in $FILES
do
  echo "Processing $f file..."

  x=(${f//.dot/ })
  y=(${x//// })
  name=${y[1]}
  echo $name
  dot -Tpng $f > "rules_imgs/"$name".png"
  # take action on each file. $f store current file name
done

mkdir -p $1


python create_latex_valid.py > $1/valid_signs.tex

python create_latex_other_signs.py > $1/other_signs.tex

python create_latex_rules.py > $1/other_rules.tex



cd $1

pdflatex valid_signs.tex
pdflatex other_signs.tex
pdflatex other_rules.tex