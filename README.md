# Atividade prática
## Processamento de Imagens
> Lucas Hideki Okido
<p>Como funciona: O usuário deve colocar fotos do formato compactado .pgh dentro do diretório 'imagens-pgh'

Fazer a construção do arquivo binário do Makefile
</p>

`make all`
<p>e depois rodar usando.
</p>

`./decode imagens-pgh/imagem.pgh`

<i>Nota: importante chamar o diretório em que a imagem está, se estiver no diretório root, deve chamar apenas pelo nome do arquivo.</i>

<p>No fim, o código será executado e construirá a imagem respectiva do código no arquivo <b>imagem</b>-result.pgm no mesmo diretório do arquivo pgh.

Após a execução, pode realizar uma limpa digitando no terminal
</p>

`make clean`
<p>Fazendo isso, apagará o arquivo binário construído.</p>