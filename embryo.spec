%define _missing_doc_files_terminate_build 0

%{!?_rel:%{expand:%%global _rel 0.enl%{?dist}}}

Summary: A small virtual machine engine (in a library) and bytecode compiler
Name: embryo
Version: 1.7.7
Release: %{_rel}
License: BSD
Group: System Environment/Libraries
Source: %{name}-%{version}.tar.gz
Packager: %{?_packager:%{_packager}}%{!?_packager:Michael Jennings <mej@eterm.org>}
Vendor: %{?_vendorinfo:%{_vendorinfo}}%{!?_vendorinfo:The Enlightenment Project (http://www.enlightenment.org/)}
Distribution: %{?_distribution:%{_distribution}}%{!?_distribution:%{_vendor}}
URL: http://www.enlightenment.org/
BuildRoot: %{_tmppath}/%{name}-%{version}-root

%description
Embryo is a tiny library designed as a virtual machine to interpret a
limited set of small compiled programs.

%package devel
Summary: Embryo headers, static libraries, documentation and test programs
Group: System Environment/Libraries
Requires: %{name} = %{version}

%description devel
Headers, static libraries, test programs and documentation for Embryo

%package bin
Summary: Embryo bytecode compiler and needed data files
Group: System Environment/Libraries
Requires: %{name} = %{version}

%description bin
The embryo bytecode compiler and its files

%prep
%setup -q

%build
%{configure} --prefix=%{_prefix}
### use this if you have build problems
#./configure --prefix=%{_prefix}
%{__make} %{?_smp_mflags} %{?mflags}

%install
%{__make} %{?mflags_install} DESTDIR=$RPM_BUILD_ROOT install

%clean
test "x$RPM_BUILD_ROOT" != "x/" && rm -rf $RPM_BUILD_ROOT

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%defattr(-, root, root)
%doc AUTHORS COPYING* README
%{_libdir}/*.so.*

%files bin
%defattr(-, root, root)
%attr(755,root,root) %{_bindir}/embryo_cc
%{_datadir}/embryo/include

%files devel
%defattr(-, root, root)
%{_libdir}/*.so
%{_libdir}/*.la
%{_libdir}/*.a
%{_libdir}/pkgconfig/*
%{_includedir}/embryo-1/*.h

%changelog
