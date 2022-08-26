import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart              #imporatation des modules 
from tkinter.messagebox import *
from tkinter import *
from cryptography.fernet import Fernet
import webbrowser

def open_gmail(decrypt_page):
    webbrowser.open_new("https://mail.google.com")
    decrypt2_pagefct(decrypt_page)
    


def encrypt(a,key):    #fonction d'encyptage
    message = (a).encode() #encodage de la chaine de caractère en bytes

    f = Fernet(key) #raccourcissement de la variable clé
    encrypted = f.encrypt(message) #cryptage de la clé
    return encrypted


def decrypt(encrypted,key):    #fonction de décryptage 
    i=0
    encryptedWithoutB=""
    while i<len(encrypted):
        if i!=0 and i!=1 and i!=len(encrypted):
            encryptedWithoutB+=encrypted[i]
        i+=1
    b=(encryptedWithoutB).encode()
    f = Fernet(key) #raccourcissement de la variable clé
    
    decrypted = f.decrypt(b)
    return decrypted

def main():
    #personaliser fenetre 
    window = Tk()                        #crée la page 
    window.title("Turing nightmare")     #donner le titre à la page
    window.wm_iconbitmap('matrix.ico')   #donner une icone à la page

    #frame

    photo = PhotoImage(file= "Matrix.png")          #mettre un fond à page 
    window.resizable(width=False,height=False)      #empecher de modifier la taille de la page 
    Canevas= Canvas(window, width=720,height=480)
    item = Canevas.create_image(0,0,anchor=NW,image=photo)  #placer l'image
    Canevas.pack()

    
    #titre
    label_title=Label(window, text="decrypter ou encrypter",font=("Courrier", 40), bg='black',fg='green').place(x='100',y='100')
    

    #sous-titre
    label_subtitle=Label(window, text="un message",font=("courrier", 30), bg='black',fg='green' ).place(x='250',y='160')
    

    #ajouter  bouton
    my_button=Button(window,text ="encrypter",font=("Arial", 25), bg='green',fg='black',command = lambda : encrypt_pagefct(window)).place(x='100',y='300')
    my_button=Button(window,text ="decrypter",font=("Arial", 25), bg='green',fg='black',command = lambda : decrypt_pagefct(window)).place(x='450',y='300')

    #ajouter la frame

    window.mainloop()

def encrypt_pagefct(window):  
    window.destroy()
    encrypt_page=Tk()
    encrypt_page.wm_iconbitmap('matrix.ico')
    encrypt_page.title("Turing nightmare")
    encrypt_page.geometry("600x200")
    encrypt_page.resizable(width=False, height=False)
    encrypt_page.config(background='black')
    
    label_title=Label(encrypt_page, text="Entrer le mail du destinataire",font=("Courrier", 30), bg='black',fg='green')
    label_title.pack()
    
    send_to_email=StringVar() #email variable
    
    encrypt_entry=Entry(textvariable=send_to_email,font=('courrier',15),bg='black',fg='green')
    encrypt_entry.focus_set()
    encrypt_entry.pack()

    encrypt_page_button=Button(encrypt_page,text ="Valider l'adresse",font=("Arial", 25), bg='green',fg='black',command = lambda : encrypt2_pagefct(encrypt_entry,encrypt_page))
    encrypt_page_button.pack()
    
    

def encrypt2_pagefct(encrypt_entry,encrypt_page):
    send_to_email=encrypt_entry.get()
    encrypt_page.destroy()
    encrypt2_page=Tk()
    encrypt2_page.wm_iconbitmap('matrix.ico')
    encrypt2_page.title("Turing nightmare")
    encrypt2_page.geometry("600x200")
    encrypt2_page.resizable(width=False, height=False)
    encrypt2_page.config(background='black')
    
    label_title=Label(encrypt2_page, text="Entrer le message à envoyer",font=("Courrier", 30), bg='black',fg='green')
    label_title.pack()
    
    message=StringVar() #message variable
    
    encrypt2_entry=Entry(textvariable=message,font=('courrier',15),bg='black',fg='green',width ='40' )
    encrypt2_entry.focus_set()
    encrypt2_entry.pack()
    
    encrypt2_page_button=Button(encrypt2_page,anchor="s",text ="Envoyer",font=("Arial", 25), bg='green',fg='black',command = lambda : envoyer_mail(send_to_email,encrypt2_entry,encrypt2_page))
    encrypt2_page_button.pack()

def envoyer_mail (send_to_email,encrypt2_entry,encrypt2_page) : #module d'envoi de l'email
    
    messageVar=encrypt2_entry.get()

    messageCrypte=str(encrypt(messageVar,key))
    

    encrypt2_page.destroy()
    
    email = 'projetmessagerieISN@gmail.com'
    password = 'lemotdepasseduprojet'
    subject = 'message crypté projet ISN'
    
    msg = MIMEMultipart()
    msg['From'] = email
    msg['To'] = send_to_email
    msg['Subject'] = subject
    
    msg.attach(MIMEText(messageCrypte, 'plain'))
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(email, password)
    text = msg.as_string() 
    server.sendmail(email, send_to_email, text)
    server.quit()
    main()




def decrypt_pagefct (window):
    window.destroy()
    decrypt_page=Tk()
    decrypt_page.wm_iconbitmap('matrix.ico')
    decrypt_page.title("Turing nightmare")
    decrypt_page.geometry("600x200")
    decrypt_page.resizable(width=False, height=False)
    decrypt_page.config(background='black')
    label_title=Label(decrypt_page, text="Ouvrir Gmail ? ",font=("Courrier", 30), bg='black',fg='green')
    label_title.pack()
    
    
    
    decrypt_page_button=Button(decrypt_page,text =" OUI ",font=("Arial", 25), bg='green',fg='black',command = lambda : open_gmail(decrypt_page))
    decrypt_page_button.pack()

    decrypt_page_button=Button(decrypt_page,text ="NON",font=("Arial", 25), bg='green',fg='black',command = lambda : decrypt2_pagefct(decrypt_page))
    decrypt_page_button.pack()
    

def decrypt2_pagefct(decrypt_page):
    
    decrypt_page.destroy()
    
    decrypt2_page=Tk()
    decrypt2_page.wm_iconbitmap('matrix.ico')
    decrypt2_page.title("Turing nightmare")
    decrypt2_page.geometry("600x200")
    decrypt2_page.resizable(width=False, height=False)
    decrypt2_page.config(background='black')
    label_title=Label(decrypt2_page, text="entrer le message à decrypter",font=("Courrier", 30), bg='black',fg='green')
    label_title.pack()

    messageADecrypt=StringVar()
    decrypt2_entry=Entry(textvariable=messageADecrypt,font=('courrier',15),bg='black',fg='green',width ='40' )
    decrypt2_entry.focus_set()
    decrypt2_entry.pack()
    
    encrypt2_page_button=Button(decrypt2_page,text ="decrypter",font=("Arial", 25), bg='green',fg='black',command = lambda : decrypt3_pagefct(decrypt2_page,decrypt2_entry))
    encrypt2_page_button.pack()





def decrypt3_pagefct(decrypt2_page,decrypt2_entry):
    
    messageDecryptVar=str(decrypt2_entry.get())
    messageDecrypt=decrypt(messageDecryptVar,key)
    decrypt2_page.destroy()
    decrypt3_page=Tk()
    decrypt3_page.wm_iconbitmap('matrix.ico')
    decrypt3_page.title("Turing nightmare")
    decrypt3_page.geometry("600x200")
    decrypt3_page.config(background='black')
    label_title=Label(decrypt3_page, text=messageDecrypt,font=("Courrier", 30), bg='black',fg='green')
    label_title.pack()

    encrypt3_page_button=Button(decrypt3_page,text ="Quitter",font=("Arial", 25), bg='green',fg='black',command = lambda : decrypt3_page.destroy())
    encrypt3_page_button.pack()








'''f=open("key.txt",mode="r")
for line in f:
    key=line'''
key = b'5zl6vhBG_K3RddkV96v4HB0sQ-EJnEQldyEuFpQouVw='



main()

