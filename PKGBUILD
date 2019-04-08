pkgname=dwm
pkgver=6.1
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'terminus-font' 'ttf-freefont' 'rxvt-unicode' 'chromium' 'dmenu' 'xscreensaver')
provides=('dwm')
conflicts=('dwm')
epoch=1
source=("http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz"
        "config.mk.diff"
        "config.h"
        "dwm-nametag-prepend-6.1.diff"
        "http://lists.suckless.org/dev/att-27712/dwm-6.1-togglefullscreen.diff"
        "https://dwm.suckless.org/patches/pertag/dwm-pertag-6.1.diff"
        )
md5sums=('f0b6b1093b7207f89c2a90b848c008ec'
         'e2b8ebee2b8bb45049df9115ed030bb9'
         'SKIP'
         'ac4a03571c5c2471f540ee268ea724d8'
         'cfe5c1d54ed55bcef0d19aa9c067d959'
         '3126263695676ffa7ab7d90e49bd77cb'
         )

build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  patch -p1 -i $srcdir/dwm-nametag-prepend-6.1.diff
  patch -p1 -i $srcdir/dwm-6.1-togglefullscreen.diff
  patch -p0 -i $srcdir/config.mk.diff
  patch -p1 -i $srcdir/dwm-pertag-6.1.diff
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
} # vim:set ts=2 sw=2 et:
