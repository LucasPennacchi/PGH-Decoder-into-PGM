# Atividade prática
## Processamento de Imagens

Como funciona. O usuário deve colocar fotos do formato compactado .pgh dentro do diretório 'imagens-pgh'
Fazer a construção do arquivo binário do Makefile 
`make all`
e depois rodar usando.
`./decode imagens-pgh/imagem.pgh`

<i>Nota: importante chamar o diretório em que a imagem está, se estiver no diretório root, deve chamar apenas pelo nome do arquivo.</i>

No fim, o código será executado e construirá a imagem respectiva do código no arquivo <b>imagem</b>-result.pgm no mesmo diretório do arquivo pgh respectivo.

Após a execução, pode realizar uma limpa digitando no terminal
`make clean`

Fazendo isso, apagará o arquivo binário construído.