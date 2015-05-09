#===============================================================================
#
# The autoconf configuration file for mysql-smiles
#
# @author Jack
# @version 1.0
# @date Fri May  8 12:56:58 2015
#
#===============================================================================

AC_PREREQ([2.63])
AC_INIT(mysql-smiles, 1.0, http://github.com/guitarpoet/mysql-smiles)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/smiles.cc])
AM_INIT_AUTOMAKE
AC_ENABLE_SHARED
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Check for mysql plugin folders
MYSQL_PLUGIN_FOLDERS="/usr/local/lib/mysql /usr/lib/mysql /usr/lib64/mysql/mysql /opt/local/lib/mysql /opt/local/lib/mysql55 /opt/local/lib/mysql56"

AC_MSG_CHECKING(mysql plugin folder)

if test -z "$MYSQL_PLUGIN_DIR"; then
	for i in $MYSQL_PLUGIN_FOLDERS; do
		if test -d $i/plugin; then
			MYSQL_PLUGIN_DIR=$i/plugin
		fi
	done
fi

if test -z "$MYSQL_PLUGIN_DIR"; then
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(No mysql plugin folder found, please configure variable MYSQL_PLUGIN_DIR!)
else
	AC_MSG_RESULT(yes)
	AC_SUBST([pkgplugindir], [$MYSQL_PLUGIN_DIR])
fi

# Checks for libraries.

AC_MSG_CHECKING(openbabel libs)
OBABEL_LIB_SEARCH_DIRS="/usr/local/lib /usr/local/lib64 /usr/lib /usr/lib64 /opt/local/lib /opt/local/lib64"
for i in $OBABEL_LIB_SEARCH_DIRS; do
	if test -f $i/libopenbabel.dylib; then
		OBABEL_LD_DIR=$i
	fi
	if test -f $i/libopenbabel.so; then
		OBABEL_LD_DIR=$i
	fi
done

if test -z "$OBABEL_LD_DIR"; then
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(No openbabel library found!)
else
	AC_MSG_RESULT(yes)
fi

# Set the load flags
LDFLAGS="-L$OBABEL_LD_DIR -lopenbabel -lstdc++ $LDFLAGS"

# Checks for header files.
OBABEL_SEARCH_DIRS="/usr/local/include /usr/include /opt/local/include /usr/local/src /opt/local/src"

AC_MSG_CHECKING(openbabel headers)
for i in $OBABEL_SEARCH_DIRS; do
	if test -f $i/openbabel-2.0/openbabel/mol.h; then
		OBABEL_INCDIR=$i/openbabel-2.0/
	fi
done

if test -z "$OBABEL_INCDIR"; then
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(No openbabel header found!)
else
	AC_MSG_RESULT(yes)
fi

MYSQL_SEARCH_DIRS="/usr/local/include /usr/include /opt/local/include /opt/local/include/mysql55 /opt/local/include/mysql56"

AC_MSG_CHECKING(mysql headers)
for i in $MYSQL_SEARCH_DIRS; do
	if test -f $i/mysql/mysql.h; then
		MYSQL_INCDIR=$i/mysql
	fi
done

if test -z "$MYSQL_INCDIR"; then
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(No mysql header found!)
else
	AC_MSG_RESULT(yes)
fi

# Set the include flags

CPPFLAGS="-I$MYSQL_INCDIR -I$OBABEL_INCDIR $CPPFLAGS"

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile src/Makefile)
