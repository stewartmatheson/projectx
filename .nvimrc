nnoremap <silent> <F9> :!build/ProjectX<CR>
nnoremap <silent> <F10> :!build/ProjectX ./assets/maps/room.bin<CR>
autocmd BufWritePre *.h,*.hpp,*.c,*.cpp :Format
