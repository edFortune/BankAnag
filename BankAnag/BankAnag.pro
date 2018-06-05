HEADERS += \
    fenprincipale.h \
    fen_client/fen_inscription.h \
    fen_client/fen_clientProfile/fen_clientprofile.h \
    fen_client/fen_clientProfile/fen_clientprofile_document_delegate.h \
    fen_client/fen_listeClient.h \
    fen_transaction/fen_listetransaction.h \
    fen_transaction/fen_transaction.h \
    fen_transaction/fen_transactioninfo.h \
    fen_transaction/fen_transaction_delegate.h \
    fen_client/fen_donneeclient.h \
    fen_homepage.h \
    fen_settingsOptions/fen_settings.h \
    fen_impression/fen_impression.h \
    databaseclass.h \
    fen_caisseOptions/fen_depense.h \
    fen_caisseOptions/fen_caisse.h \
    fen_caisseOptions/fen_caisse_delegate.h \
    fen_caisseOptions/fen_caisse_delegate2.h \
    fen_rapportgeneralOptions/fen_rapportgeneral.h \
    widgetStyleHeader.h \
    DesignWidgets/dpushbutton.h \
    fen_investissement/Produit/investissement.h \
    DesignWidgets/dlineedit.h \
    fen_investissement/Produit/produitinvestments.h \
    DesignWidgets/ddateedit.h \
    DesignWidgets/dgroupbox.h \
    DesignWidgets/dcombobox.h \
    DesignWidgets/dtextedit.h \
    DesignWidgets/ddoublespinbox.h \
    DesignWidgets/dspinbox.h \
    fen_investissement/Service/serviceinvestments.h \
    fen_investissement/Produit/produit.h \
    fen_investissement/Produit/fournisseur.h \
    DesignWidgets/dlabel.h \
    fen_investissement/Produit/investmentmanagement.h \
    fen_investissement/Produit/investments.h \
    fen_investissement/Produit/creditinvestment.h \
    fen_investissement/Produit/investmenttransaction.h \
    fen_investissement/Produit/produittransaction.h \
    fen_investissement/Produit/customitemdelegates.h \
    fen_investissement/Produit/client.h \
    fen_investissement/Service/servicemanagement.h \
    fen_investissement/Service/service.h \
    fen_investissement/Service/emprunteur.h \
    fen_impression/impression.h \
    include/firebase/admob/banner_view.h \
    include/firebase/admob/interstitial_ad.h \
    include/firebase/admob/native_express_ad_view.h \
    include/firebase/admob/rewarded_video.h \
    include/firebase/admob/types.h \
    include/firebase/analytics/event_names.h \
    include/firebase/analytics/parameter_names.h \
    include/firebase/analytics/user_property_names.h \
    include/firebase/auth/credential.h \
    include/firebase/auth/types.h \
    include/firebase/auth/user.h \
    include/firebase/database/common.h \
    include/firebase/database/data_snapshot.h \
    include/firebase/database/database_reference.h \
    include/firebase/database/disconnection.h \
    include/firebase/database/listener.h \
    include/firebase/database/mutable_data.h \
    include/firebase/database/query.h \
    include/firebase/database/transaction.h \
    include/firebase/dynamic_links/components.h \
    include/firebase/internal/common.h \
    include/firebase/internal/future_impl.h \
    include/firebase/storage/common.h \
    include/firebase/storage/controller.h \
    include/firebase/storage/listener.h \
    include/firebase/storage/metadata.h \
    include/firebase/storage/storage_reference.h \
    include/firebase/admob.h \
    include/firebase/analytics.h \
    include/firebase/app.h \
    include/firebase/auth.h \
    include/firebase/database.h \
    include/firebase/dynamic_links.h \
    include/firebase/future.h \
    include/firebase/instance_id.h \
    include/firebase/invites.h \
    include/firebase/log.h \
    include/firebase/messaging.h \
    include/firebase/remote_config.h \
    include/firebase/storage.h \
    include/firebase/util.h \
    include/firebase/variant.h \
    include/firebase/version.h \
    include/google_play_services/availability.h \
    firestorerestapimanager.h



SOURCES += \
    fenprincipale.cpp \
    fenMain.cpp \
    fen_client/fen_inscription.cpp \
    fen_client/fen_clientProfile/fen_clientprofile.cpp \
    fen_client/fen_clientProfile/fen_clientprofile_listetransaction.cpp \
    fen_client/fen_clientProfile/fen_clientprofile_documents.cpp \
    fen_client/fen_clientProfile/fen_clientprofile_document_delegate.cpp \
    fen_client/fen_listeClient.cpp \
    fen_transaction/fen_listetransaction.cpp \
    fen_transaction/fen_transaction.cpp \
    fen_transaction/fen_transactioninfo.cpp \
    fen_transaction/fen_transaction_delegate.cpp \
    fen_client/fen_donneeclient.cpp \
    fen_homepage.cpp \
    fen_impression/fen_impression.cpp \
    databaseclass.cpp \
    fen_settingsOptions/fen_settings.cpp  \
    fen_settingsOptions/fen_settings_listeclient.cpp \
    fen_settingsOptions/fen_settings_listetransaction.cpp \
    widgetStyleSource.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral_client.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral_transaction.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral_echangeUSD.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral_achatVente.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral_depense.cpp \
    fen_rapportgeneralOptions/fen_rapportgeneral_caisse.cpp \
    fen_caisseOptions/fen_depense.cpp \
    fen_caisseOptions/fen_caisse.cpp \
    fen_caisseOptions/fen_caisse_delegate.cpp \
    fen_caisseOptions/fen_caisse_delegate2.cpp \
    fen_caisseOptions/fen_caisse_rapportcaisse.cpp \
    fen_caisseOptions/fen_caisse_rapportechangeus.cpp \
    fen_caisseOptions/fen_caisse_rapportachatvente.cpp \
    fen_caisseOptions/fen_caisse_autreproduits.cpp \
    DesignWidgets/dpushbutton.cpp \
    fen_investissement/Produit/investissement.cpp \
    DesignWidgets/dlineedit.cpp \
    fen_investissement/Produit/produitinvestments.cpp \
    DesignWidgets/ddateedit.cpp \
    DesignWidgets/dgroupbox.cpp \
    DesignWidgets/dcombobox.cpp \
    DesignWidgets/dtextedit.cpp \
    DesignWidgets/ddoublespinbox.cpp \
    DesignWidgets/dspinbox.cpp \
    fen_investissement/Service/serviceinvestments.cpp \
    fen_investissement/Produit/produit.cpp \
    fen_investissement/Produit/fournisseur.cpp \
    DesignWidgets/dlabel.cpp \
    fen_investissement/Produit/investmentmanagement.cpp \
    fen_investissement/Produit/investments.cpp \
    fen_investissement/Produit/creditinvestment.cpp \
    fen_investissement/Produit/investmenttransaction.cpp \
    fen_investissement/Produit/produittransaction.cpp \
    fen_investissement/Produit/client.cpp \
    fen_investissement/Service/servicemanagement.cpp \
    fen_investissement/Service/service.cpp \
    fen_investissement/Service/emprunteur.cpp \
    fen_impression/impression.cpp \
    firestorerestapimanager.cpp



TARGET = BankAnag

QT  += sql printsupport network

FORMS +=

OTHER_FILES +=

DISTFILES += \
    style.qss \
    style.qss.GU5004 \
    style.qss.oO5004 \
    style.qss.qn5980 \
    style.qss.rZ5004



