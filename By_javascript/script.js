// ================= CAESAR =================
function caesarEncrypt(text, key) {
  key = parseInt(key) || 3;
  return text.split('').map(ch => {
    if (/[a-z]/.test(ch)) return String.fromCharCode((ch.charCodeAt(0)-97+key)%26+97);
    if (/[A-Z]/.test(ch)) return String.fromCharCode((ch.charCodeAt(0)-65+key)%26+65);
    return ch;
  }).join('');
}
function caesarDecrypt(text, key) { return caesarEncrypt(text, 26-(parseInt(key)||3)); }

// ================= AFFINE =================
function affineEncrypt(text, key) {
  let [a,b] = key.split(',').map(Number); if(!a||!b) return text;
  return text.split('').map(ch=>{
    if(/[a-z]/.test(ch)) return String.fromCharCode(((a*(ch.charCodeAt(0)-97)+b)%26)+97);
    if(/[A-Z]/.test(ch)) return String.fromCharCode(((a*(ch.charCodeAt(0)-65)+b)%26)+65);
    return ch;
  }).join('');
}
function modInverse(a,m){ for(let x=1;x<m;x++) if((a*x)%m==1) return x; return 1; }
function affineDecrypt(text, key) {
  let [a,b] = key.split(',').map(Number); let a_inv=modInverse(a,26);
  return text.split('').map(ch=>{
    if(/[a-z]/.test(ch)) return String.fromCharCode(((a_inv*((ch.charCodeAt(0)-97)-b+26))%26)+97);
    if(/[A-Z]/.test(ch)) return String.fromCharCode(((a_inv*((ch.charCodeAt(0)-65)-b+26))%26)+65);
    return ch;
  }).join('');
}

// ================= PERMUTATION =================
function permutationEncrypt(text, key) {
  let n = key.length; let perm = key.split('').map(Number); let result='';
  for(let i=0;i<text.length;i+=n){
    let block=text.substr(i,n).padEnd(n,'X');
    let out=new Array(n);
    for(let j=0;j<n;j++) out[j]=block[perm[j]-1];
    result+=out.join('');
  }
  return result;
}
function permutationDecrypt(text, key) {
  let n = key.length; let perm=key.split('').map(Number); let result='';
  for(let i=0;i<text.length;i+=n){
    let block=text.substr(i,n); let out=new Array(n);
    for(let j=0;j<n;j++) out[perm[j]-1]=block[j];
    result+=out.join('');
  }
  return result;
}

// ================= VIGENERE =================
function vigenereEncrypt(text, key){
  key=key.toUpperCase(); let j=0;
  return text.split('').map(ch=>{
    if(/[A-Z]/.test(ch)){let c=(ch.charCodeAt(0)-65+(key[j++%key.length].charCodeAt(0)-65))%26+65;return String.fromCharCode(c);}
    if(/[a-z]/.test(ch)){let c=(ch.charCodeAt(0)-97+(key[j++%key.length].charCodeAt(0)-65))%26+97;return String.fromCharCode(c);}
    return ch;
  }).join('');
}
function vigenereDecrypt(text, key){
  key=key.toUpperCase(); let j=0;
  return text.split('').map(ch=>{
    if(/[A-Z]/.test(ch)){let c=(ch.charCodeAt(0)-65-(key[j++%key.length].charCodeAt(0)-65)+26)%26+65;return String.fromCharCode(c);}
    if(/[a-z]/.test(ch)){let c=(ch.charCodeAt(0)-97-(key[j++%key.length].charCodeAt(0)-65)+26)%26+97;return String.fromCharCode(c);}
    return ch;
  }).join('');
}

// ================= PLAYFAIR =================
function generateMatrix(key){
  key=(key+ "ABCDEFGHIKLMNOPQRSTUVWXYZ").toUpperCase().replace(/J/g,"I");
  let seen={}; let matrix=[]; for(let ch of key){ if(!seen[ch]){ matrix.push(ch); seen[ch]=true; } }
  return matrix;
}
function playfairProcess(text){ return text.toUpperCase().replace(/J/g,"I").replace(/[^A-Z]/g,"").replace(/(.)(?=\1)/g,"$1X"); }
function playfairEncrypt(text,key){
  let m=generateMatrix(key); let res=''; text=playfairProcess(text);
  for(let i=0;i<text.length;i+=2){let a=m.indexOf(text[i]),b=m.indexOf(text[i+1]||'X');
    let r1=Math.floor(a/5),c1=a%5,r2=Math.floor(b/5),c2=b%5;
    if(r1==r2){res+=m[r1*5+(c1+1)%5]+m[r2*5+(c2+1)%5];}
    else if(c1==c2){res+=m[((r1+1)%5)*5+c1]+m[((r2+1)%5)*5+c2];}
    else{res+=m[r1*5+c2]+m[r2*5+c1];}}
  return res;
}
function playfairDecrypt(text,key){
  let m=generateMatrix(key); let res='';
  for(let i=0;i<text.length;i+=2){let a=m.indexOf(text[i]),b=m.indexOf(text[i+1]);
    let r1=Math.floor(a/5),c1=a%5,r2=Math.floor(b/5),c2=b%5;
    if(r1==r2){res+=m[r1*5+(c1+4)%5]+m[r2*5+(c2+4)%5];}
    else if(c1==c2){res+=m[((r1+4)%5)*5+c1]+m[((r2+4)%5)*5+c2];}
    else{res+=m[r1*5+c2]+m[r2*5+c1];}}
  return res;
}

// ================= MAIN =================
function encrypt(){
  let algo=document.getElementById('algo').value;
  let key=document.getElementById('key').value;
  let text=document.getElementById('inputText').value;
  let result='';
  switch(algo){
    case 'caesar': result=caesarEncrypt(text,key);break;
    case 'affine': result=affineEncrypt(text,key);break;
    case 'permutation': result=permutationEncrypt(text,key);break;
    case 'vigenere': result=vigenereEncrypt(text,key);break;
    case 'playfair': result=playfairEncrypt(text,key);break;
  }
  document.getElementById('outputText').value=result;
}
function decrypt(){
  let algo=document.getElementById('algo').value;
  let key=document.getElementById('key').value;
  let text=document.getElementById('inputText').value;
  let result='';
  switch(algo){
    case 'caesar': result=caesarDecrypt(text,key);break;
    case 'affine': result=affineDecrypt(text,key);break;
    case 'permutation': result=permutationDecrypt(text,key);break;
    case 'vigenere': result=vigenereDecrypt(text,key);break;
    case 'playfair': result=playfairDecrypt(text,key);break;
  }
  document.getElementById('outputText').value=result;
}

// ================= TIỆN ÍCH =================
function copyResult() {
  let output = document.getElementById("outputText");
  if (output.value.trim() !== "") {
    navigator.clipboard.writeText(output.value);
    alert("Đã copy kết quả vào clipboard!");
  } else {
    alert("Không có dữ liệu để copy!");
  }
}

function resetForm() {
  document.getElementById("algo").selectedIndex = 0;
  document.getElementById("key").value = "";
  document.getElementById("inputText").value = "";
  document.getElementById("outputText").value = "";
  showHint();
}

// Gợi ý nhập khóa
function showHint(){
  let algo=document.getElementById("algo").value;
  let hint=document.getElementById("hint");
  switch(algo){
    case "caesar": hint.innerText="Ví dụ khóa: số nguyên (3)"; break;
    case "affine": hint.innerText="Ví dụ khóa: a,b (3,5) với a nguyên tố cùng 26"; break;
    case "permutation": hint.innerText="Ví dụ khóa: chuỗi số hoán vị (312)"; break;
    case "vigenere": hint.innerText="Ví dụ khóa: chuỗi chữ (LEMON)"; break;
    case "playfair": hint.innerText="Ví dụ khóa: chuỗi chữ (MONARCHY)"; break;
  }
}
