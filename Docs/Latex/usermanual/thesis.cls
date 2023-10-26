%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% main.cls
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Class for my master thesis
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CLASS OPTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{thesis}
\LoadClass[a4paper,english,12pt,oneside, openright]{report} % Base class

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PACKAGES REQUIRED FOR CLASS LAYOUT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\RequirePackage[utf8]{inputenc}
\RequirePackage{nomencl}
\RequirePackage{caption}
\RequirePackage{fancyhdr}
\RequirePackage{listings} 
\RequirePackage{hyperref}
\RequirePackage{subcaption}
\RequirePackage{makeidx}
\RequirePackage{float}
\RequirePackage{a4wide}
\RequirePackage[dvipsnames]{xcolor}
\RequirePackage[DIV=14,BCOR=15mm,headinclude=false,footinclude=false, 1.1headlines, mpinclude=false, pagesize]{typearea}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CLASS OPTIONS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% \renewcommand{\nomitemsep}{-\parsep}
\setlength{\nomlabelwidth}{.20\hsize}
\setlength{\voffset}{+0.5cm}


% Captiondefinition
\captionsetup{font=small,labelfont=bf}% evtl. eins kleiner schalten

\renewcommand{\baselinestretch}{1.5}

\newcommand{\changefont}[3]{\fontfamily{#1} \fontseries{#2} \fontshape{#3} \selectfont}

\pagestyle{fancy} 
\fancyhf{}
\fancyhead[OR]{						 	% "O" steht f�r "odd", also ungerade Seiten; "L" steht f�r links
	\color{black}
	\changefont{pag}{m}{n}
	\bfseries\leftmark
}
\fancyhead[EL]{ % "E" f�r "even", also gerade Seiten; "R" steht f�r rechts
%\fancyhead[L]{
	\color{black}
	\changefont{pag}{m}{n}
	\bfseries\rightmark
}
\renewcommand{\chaptermark}[1]{\markboth{#1}{}}
\renewcommand{\sectionmark}[1]{\markright{\thesection\ #1}} 
\renewcommand{\headrulewidth}{0.4pt}

\fancyfoot[OR,EL]{			
	\color{black}
	\changefont{pag}{m}{n}
	\bfseries\thepage
}
\renewcommand{\footrulewidth}{0.4pt}

\fancypagestyle{plain}{
    \fancyhead{}
    \renewcommand{\headrulewidth}{0pt}
    \renewcommand{\footrulewidth}{0.4pt}
}

\renewcommand{\headrule}{{\color{black}
	\hrule width\headwidth height\headrulewidth 
    \vskip-\headrulewidth}
}

\renewcommand{\footrule}{{\color{black}
	\hrule width\headwidth height\headrulewidth 
    \vskip-\headrulewidth \vspace{2mm}}
}

% \hfuzz=0.1pt \vfuzz=0.1pt \hbadness=1000 \vbadness=1000 \tolerance=8000

% \setlength{\hoffset}{0cm}
% \setlength{\textheight}{23.4cm}
% \setlength{\textwidth}{16cm}
% \setlength{\footskip}{1.1cm}
% \setlength{\headsep}{1cm}

%set typearea



% \setlength{\subfigcapskip}{-10pt} \setlength{\subfigtopskip}{-10pt} \setcounter{tocdepth}{2}

\renewcommand{\bottomfraction}{0.7}
\renewcommand{\textfraction}{0.05}

%fügt unter dem Befehl \RN{"Zahl"} die entsprechende Zahl in römischer Schreibweise ein
\newcommand{\RN}[1]{\uppercase\expandafter{\romannumeral#1}}

\setlength{\parindent}{1.5em}

\nonfrenchspacing

\hyphenation{Ladungs-trager-dichte Beispiel-wort}

\makeindex

\lstset{
    language=C++,
    basicstyle=\ttfamily,
    keywordstyle=\color{blue},
    commentstyle=\color{green},
    morecomment=[l][\color{magenta}]{\#},
    numbers=left,
    numberstyle=\tiny\color{gray},
    breaklines=true,
    frame=single,
    showstringspaces=false,
}
\hypersetup{hypertexnames=true}

\setlength\parindent{0pt}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% FILTER IRRELEVANT WARNINGS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\RequirePackage{silence}

% The page header is deliberately disabled in my-resume, so the warning by scrlayer-scrpage is invalid. 
\WarningFilter{fancyhdr}{\headheight is too small (12.0pt)}
