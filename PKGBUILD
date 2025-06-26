pkgname=dwm
pkgver=6.5
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'terminus-font' 'gnu-free-fonts' 'rxvt-unicode' 'dmenu' 'xscreensaver' 'acpi' 'dunst' 'bash-completion' 'encfs' 'synaptics' 'alsa-utils' 'pkg-config' 'pulseaudio' 'pulseaudio-alsa' 'pavucontrol' 'conky' 'openvpn' 'patch' 'base-devel' 'scrot' 'feh' 'thunar' 'zip' 'unzip' 'jq' 'xorg-xsetroot')
provides=('dwm')
conflicts=('dwm')
epoch=1
source=("http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz"
        "config.h"
        "https://dwm.suckless.org/patches/nametag/dwm-nametag-prepend-6.2.diff"
        "https://dwm.suckless.org/patches/canfocusfloating/dwm-canfocusfloating-20210724-b914109.diff"
        "https://dwm.suckless.org/patches/pertag/dwm-pertag-20200914-61bb8b2.diff"
        "dwm-keysh.diff"
        )
md5sums=('446e84f5b151a1d4483fd72fd647e47e'
         'SKIP'
         'a1e618145a60d2e70b42334177e7cca1'
         '871cc0712e450e0dfb5e44f324f48687'
         'fe418b7cf2e01f59c05595a8336e6020'
         'SKIP'
         )

function echopatch() {
  echo $*
  $*
}

build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  echopatch patch -p1 -i $srcdir/dwm-canfocusfloating-20210724-b914109.diff
  echopatch patch -p1 -i $srcdir/dwm-nametag-prepend-6.2.diff
  echopatch patch -p1 -i $srcdir/dwm-keysh.diff
  echopatch patch -p1 -i $srcdir/dwm-pertag-20200914-61bb8b2.diff
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
}

# vim:set ts=2 sw=2 et:
