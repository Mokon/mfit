#!/bin/bash

# Aux function append to a file.
function print {
  local text="$1"
  local file=${2:-daily.tex}

  echo "$text" >> $file
}

# Aux function to append to a file from stdin. Useful for sending a heredoc to
# be printed.
function printhd {
  local file=${2:-daily.tex}

  read -r -d '' text
  echo -n "$text" >> $file
} 

# Aux function to echo the days of week in a specified format.
function days_of_week {
  local format=${1-"a"}

  for i in {5..11} ; do
    date -d "1/$i/1970" "+%$format"
  done
}

dsow=$(days_of_week)
macros=(Calories Fat Carbohydrates Protein Chol Sodium)
submacros=(BLANK Total Trans Sat Poly
           Total Starch Fiber Sugar BLANK BLANK BLANK)

printhd << LATEX
\documentclass{article}

\usepackage{adjustbox}
\usepackage{array}
\usepackage[margin=0.5in]{geometry}

\newcolumntype{R}[2]{%
    >{\adjustbox{angle=#1,lap=\width-(#2)}\bgroup}%
    l%
    <{\egroup}%
}
\newcommand*\rot{\multicolumn{1}{R{45}{1em}}}

\begin{document}

LATEX

print "\begin{tabular}{r||$(seq -s "c|" $((1+${#submacros[@]}))|tr -d '[:digit:]')}"
print "&"

i=0
j=0
for hdr in ${submacros[@]} ; do
  case $hdr in
    BLANK|Total)
      mhdr=${macros[$((j++))]}
      print "\rot{$mhdr}"
      ;;
     *)
      print "\rot{ }"
      ;;
  esac
  if ((i++!= ( ${#submacros[@]}-1 ) )) ; then print "&" ; fi
done
print "\\\ \hline"
print "&"

i=0
for hdr in ${submacros[@]} ; do
  case $hdr in
    BLANK|Total)
      print "\rot{ }"
      ;;
    *)
       print "\rot{$hdr}"
      ;;
  esac
  if ((i++!= ( ${#submacros[@]}-1 ) )) ; then print "&" ; fi
done
print "\\\ \hline"


printhd <<LATEX

    Breakfast        &       &       &   & & & & \\ 
\end{tabular}

\end{document}
LATEX
