printf "\ncol_inv.cub\n"
../cub3D ./error/col_inv.cub

printf "\ncol_inv2.cub\n"
../cub3D ./error/col_inv2.cub

printf "\ncol_inv3.cub\n"
../cub3D ./error/col_inv3.cub

printf "\ncol_inv4.cub\n"
../cub3D ./error/col_inv4.cub

printf "\ncol_inv5.cub\n"
../cub3D ./error/col_inv5.cub

printf "\ndir_dup.cub\n"
../cub3D ./error/dir_dup.cub

printf "\ndir_inv.cub\n"
../cub3D ./error/dir_inv.cub

printf "\ndir_none.cub\n"
../cub3D ./error/dir_none.cub

printf "\nempty.cub\n"
../cub3D ./error/empty.cub

printf "\nemptymap.cub\n"
../cub3D ./error/emptymap.cub

printf "\nflooristex.cub\n"
../cub3D ./error/flooristex.cub

printf "\nmap_nl.cub\n"
../cub3D ./error/map_nl.cub

printf "\nmap_none.cub\n"
../cub3D ./error/map_none.cub

printf "\nmap_open.cub\n"
../cub3D ./error/map_open.cub

printf "\nmap_opendiag.cub\n"
../cub3D ./error/map_opendiag.cub

printf "\nmap_opendir.cub\n"
../cub3D ./error/map_opendir.cub

printf "\nmap_opensp.cub\n"
../cub3D ./error/map_opensp.cub

printf "\nnomap.cub\n"
../cub3D ./error/nomap.cub

printf "\nres_inv.cub\n"
../cub3D ./error/res_inv.cub

printf "\nres_inv2.cub\n"
../cub3D ./error/res_inv2.cub

printf "\ntex_dup.cub\n"
../cub3D ./error/tex_dup.cub

printf "\ntex_inv.cub\n"
../cub3D ./error/tex_inv.cub

printf "\ntex_invfile.cub\n"
../cub3D ./error/tex_invfile.cub

printf "\ntex_miss.cub\n"
../cub3D ./error/tex_miss.cub

printf "\nnotacub\n"
../cub3D ./error/notacub

printf "\n./cub3D ./cub3D\n"
../cub3D ../cub3D

printf "\n./cub3D ./cub3D ./valid/1.cub\n"
../cub3D ../cub3D ./valid/1.cub

printf "\n./cub3D ./cub3D --save\n"
../cub3D ../cub3D --save

printf "\nnotafile\n"
../cub3D ./error/notafile

printf "\nnoargs\n"
../cub3D

printf "\nToo many args: ./cub3D ./valid/1.cub ./valid/2.cub\n"
../cub3D ./valid/1.cub ./valid/2.cub

printf "\nInvalid permissions\n"
../cub3D ./error/forbidden.cub

printf "\nTurlough's colours\n"
../cub3D ./error/turlough.cub

printf "\n"