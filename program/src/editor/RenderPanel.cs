using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using mframwork;

namespace editor
{
    class RenderPanel : Panel
    {
        MVector2 mouseLocal = new MVector2();

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Global.gEngineWrap.Update();
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);            
        }

        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            base.OnKeyPress(e);
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            switch (e.KeyData)
            {
                case Keys.W: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.W); break;
                case Keys.S: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.S); break;
                case Keys.A: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.A); break;
                case Keys.D: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.D); break;
                case Keys.Q: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.Q); break;
                case Keys.E: Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.E); break;
                default:
                    Global.gEngineWrap.OnKeyDown(mframwork.MKeyCode.Undefine); 
                    break;
            }
        }

        protected override void OnKeyUp(KeyEventArgs e)
        {
            base.OnKeyUp(e);

            switch (e.KeyData)
            {
                case Keys.W: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.W); break;
                case Keys.S: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.S); break;
                case Keys.A: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.A); break;
                case Keys.D: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.D); break;
                case Keys.Q: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.Q); break;
                case Keys.E: Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.E); break;
                default:
                    Global.gEngineWrap.OnKeyUp(mframwork.MKeyCode.Undefine);
                    break;
            }
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

            mouseLocal.x = e.Location.X;
            mouseLocal.y = e.Location.Y;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:
                    Global.gEngineWrap.OnMouseDown(mframwork.MKeyCode.MouseLeft, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Right:
                    Global.gEngineWrap.OnMouseDown(mframwork.MKeyCode.MouseRight, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Middle:
                    Global.gEngineWrap.OnMouseDown(mframwork.MKeyCode.MouseMid, mouseLocal);
                    break;
                default:
                    break;
            }
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);

            mouseLocal.x = e.Location.X;
            mouseLocal.y = e.Location.Y;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:
                    Global.gEngineWrap.OnMouseMove(mframwork.MKeyCode.MouseLeft, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Right:
                    Global.gEngineWrap.OnMouseMove(mframwork.MKeyCode.MouseRight, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Middle:
                    Global.gEngineWrap.OnMouseMove(mframwork.MKeyCode.MouseMid, mouseLocal);
                    break;
                default:
                    break;
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);

            mouseLocal.x = e.Location.X;
            mouseLocal.y = e.Location.Y;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:
                    Global.gEngineWrap.OnMouseUp(mframwork.MKeyCode.MouseLeft, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Right:
                    Global.gEngineWrap.OnMouseUp(mframwork.MKeyCode.MouseRight, mouseLocal);
                    break;
                case System.Windows.Forms.MouseButtons.Middle:
                    Global.gEngineWrap.OnMouseUp(mframwork.MKeyCode.MouseMid, mouseLocal);
                    break;
                default:
                    break;
            }
        }
    }
}
