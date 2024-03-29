pkgname=dwm
pkgver=6.4
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'terminus-font' 'gnu-free-fonts' 'rxvt-unicode' 'dmenu' 'xscreensaver' 'acpi' 'dunst' 'bash-completion' 'encfs' 'synaptics' 'alsa-utils' 'pkg-config')
provides=('dwm')
conflicts=('dwm')
epoch=1
source=("http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz"
        "config.h"
        "dwm-nametag-prepend-6.1.diff"
        "https://dwm.suckless.org/patches/canfocusfloating/dwm-canfocusfloating-20210724-b914109.diff"
        "dwm-keysh.diff"
        )
md5sums=('008da068c3884ae675f65b9458b43c02'
         'SKIP'
         'ac4a03571c5c2471f540ee268ea724d8'
         '871cc0712e450e0dfb5e44f324f48687'
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
  echopatch patch -p1 -i $srcdir/dwm-nametag-prepend-6.1.diff
  echopatch patch -p1 -i $srcdir/dwm-keysh.diff
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
}

# vim:set ts=2 sw=2 et:
