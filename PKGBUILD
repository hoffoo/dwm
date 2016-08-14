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
        "config.mk.diff::https://gist.githubusercontent.com/hoffoo/350e40a79e1a4914d7502bf7bd8a10b1/raw/9c439e4ca21776b7e53303419fc3218f18b3f995/gistfile1.txt"
        "config.h::https://gist.githubusercontent.com/hoffoo/bac694215a93be0093e5955b4d418fb0/raw/4089191333919ea86c65c7ebb53cf98a6f6997db/gistfile1.txt"
        "http://dwm.suckless.org/patches/dwm-statuscolors-6.1.diff"
        "http://dwm.suckless.org/patches/dwm-pertag-6.1.diff")
md5sums=('f0b6b1093b7207f89c2a90b848c008ec'
         'e2b8ebee2b8bb45049df9115ed030bb9'
         '79cdf92778c3b57f7de8784fe54f10b6'
         'ed406bed8c3278d99d3ff556f5f4f228'
         '3126263695676ffa7ab7d90e49bd77cb'
         )

build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  patch -p1 -i $srcdir/dwm-pertag-6.1.diff
  patch -p1 -i $srcdir/dwm-statuscolors-6.1.diff
  patch -p0 -i $srcdir/config.mk.diff
  make
}

package() {
  cd $pkgname-$pkgver
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
}

# vim:set ts=2 sw=2 et:
