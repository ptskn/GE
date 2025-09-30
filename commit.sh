read -p "Entrez le Product Increment (ex: PI-2025-03) : " product_increment

# Demande le numéro de Sprint
read -p "Entrez le numéro de Sprint (ex: Sprint 5) : " sprint_number

read -p "Entrez l'ID de la feature : " feature_number

# Concaténation pour le message de commit
commit_message="$product_increment - $sprint_number - $feature_number"

# Affichage du message final pour confirmation
echo -e "\nLe message de commit sera : \033[1m$commit_message\033[0m"
read -p "Confirmer ? (O/n) " -n 1 -r
echo

if [[ $REPLY =~ ^[Oo]$ ]] || [[ -z $REPLY ]]; then
    # Configuration Git (remplace par tes infos)
    git config user.name "Git CLI Bot"
    git config user.email "git-cli@example.com"

    # Création d'un fichier vide pour forcer un changement (ou utilise `git commit --allow-empty`)
    touch .gitignore  # Remplace par un fichier pertinent si besoin
    git add .gitignore

    # Commit avec le message concaténé
    git commit -m "$commit_message"

    # Push (décommente si tu veux pousser automatiquement)
    # git push

    echo "✅ Commit créé avec succès : '$commit_message'"
else
    echo "❌ Annulé."
fi
