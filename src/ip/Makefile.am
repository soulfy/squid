include $(top_srcdir)/src/Common.am
include $(top_srcdir)/src/TestHeaders.am

noinst_LTLIBRARIES = libip.la

libip_la_SOURCES = \
	IpAddress.h \
	IpAddress.cc \
	IpIntercept.h \
	IpIntercept.cc \
	QosConfig.h \
	QosConfig.cc \
	tools.cc \
	tools.h


check_PROGRAMS += testIpAddress
TESTS += testIpAddress

testIpAddress_SOURCES= \
	testIpAddress.cc \
	testIpAddress.h

nodist_testIpAddress_SOURCES= \
	$(top_srcdir)/src/tests/testMain.cc \
	$(top_srcdir)/test-suite/test_tools.cc

testIpAddress_LDADD= \
	$(top_builddir)/compat/libcompat.la \
	libip.la \
	-L$(top_builddir)/lib -lmiscutil \
	$(XTRA_LIBS) \
	$(SQUID_CPPUNIT_LA) \
	$(SQUID_CPPUNIT_LIBS)

testIpAddress_LDFLAGS= $(LIBADD_DL)
