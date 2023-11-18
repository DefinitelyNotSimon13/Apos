/**
 * @file translatablewindow.hpp
 * @author Simon Blum
 * @date 13.11.2023
 * @version 0.1_alpha.2
 * @license LGPL-V3
 * @brief Header file for the TranslatableWindow class.
 *
 * @details This file contains the declaration of the TranslatableWindow class, which is a part of the application's frontend logic.
 * The TranslatableWindow class is an abstract base class that provides a function for retranslating the user interface.
 *
 * @note The application is part of a student project and is not intended for commercial use.
 */

#pragma once

//--------------------------------------------------------------------------------------------------------------------//
namespace AposFrontend {
    /**
     * @class TranslatableWindow
     * @ingroup Ui-Functions
     * @brief An abstract base class that provides a function for retranslating the user interface.
     * @details The TranslatableWindow class is a part of the application's frontend logic.
     * It is used as a base class for other classes that need to retranslate their user interface.
     */
    class TranslatableWindow {
    public:
        /**
         * @brief Constructor for the TranslatableWindow class.
         * @ingroup Constructructors-Destructors
         * @details This constructor initializes the TranslatableWindow object.
         */
        TranslatableWindow();

        /**
         * @brief Retranslates the user interface.
         * @ingroup Ui-Functions
         * @details This is a pure virtual function that needs to be implemented by derived classes.
         * It is used to retranslate the user interface of the window.
         */
        virtual void retranslateUi() = 0;
    };
}