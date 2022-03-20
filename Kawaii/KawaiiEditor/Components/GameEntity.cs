using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Windows.Input;

namespace KawaiiEditor.Components
{
    class GameEntity
    {
        // STATE
        private bool isEnabled = true;
        private string name;
        private bool isActive;

        // PROPERTIES
        [DataMember]
        public bool IsEnabled
        {
            get => isEnabled;
            set { }
        }
        [DataMember]
        public string Name
        {
            get => name;
            set { }
        }
        public bool IsActive
        {
            get => isActive;
            set { }
        }
    }
}
