pkgname=dwm
pkgver=6.1
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft')
provides=('dwm')
conflicts=('dwm')
epoch=1
source=("http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz"
        "config.mk.diff"
        "config.h"
        "http://dwm.suckless.org/patches/dwm-statuscolors-6.1.diff"
        "http://dwm.suckless.org/patches/dwm-pertag-6.1.diff"
        "http://dwm.suckless.org/patches/dwm-nametag-prepend-6.1.diff")
md5sums=('f0b6b1093b7207f89c2a90b848c008ec'
         'e2b8ebee2b8bb45049df9115ed030bb9'
         'SKIP'
         'ed406bed8c3278d99d3ff556f5f4f228'
         '3126263695676ffa7ab7d90e49bd77cb'
         '3cedf07886745b5ec29dca458151648f'
         )

build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  patch -p1 -i $srcdir/dwm-pertag-6.1.diff
  patch -p1 -i $srcdir/dwm-statuscolors-6.1.diff
  patch -p1 -i $srcdir/dwm-nametag-prepend-6.1.diff
  patch -p0 -i $srcdir/config.mk.diff
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
}

# vim:set ts=2 sw=2 et:
