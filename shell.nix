# save this as shell.nix
{ pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
  nativeBuildInputs = [ pkgs.cmake ];
  buildInputs = [
    pkgs.fmt_8
    pkgs.SDL2
  ];
}
