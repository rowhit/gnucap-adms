# this file is part of gnucap-adms
# (c) 2012 Felix Salfelder
# license: GPLv3+

ACLOCAL_AMFLAGS = -Im4
if QUCS
QUCS=qucs
endif
SUBDIRS = src examples tests $(QUCS)
EXTRA_DIST = \
    bootstrap \
    gnuplot.mk \
    BUGS \
    NOTES

bin_SCRIPTS = gnucap-adms.mk

CLEANFILES = .*.adms .*.xml
